
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

typedef struct node {
  int key;
  int val;
  struct node *prev;
  struct node *next;
  node(int key, int val)
      : key(key), val(val), prev(nullptr), next(nullptr) {}
} NODE;

class LRUCache {
public:
  LRUCache(int size)
      : capacity(size), currSize(0) {

    // The list is ordered from most recently used after HEAD to least
    // recently used before TAIL.
    HEAD = new NODE(-1, -1); // insertion from head(most recent)
    TAIL = new NODE(-1, -1); // deletion from tail (least recent)
    HEAD->next = TAIL;
    TAIL->prev = HEAD;
  }

  LRUCache(const LRUCache &) = delete;
  LRUCache &operator=(const LRUCache &) = delete;

  ~LRUCache() {
    // Threads must be joined before destroying the cache.
    NODE *currNode = TAIL;
    while (currNode != HEAD) {
      NODE *prevNode = currNode->prev;
      currNode->prev = currNode->next = nullptr;
      delete (currNode);
      prevNode->next = nullptr;
      currNode = prevNode;
    }

    //free the head node
    HEAD->prev = HEAD->next = nullptr;
    delete (HEAD);

    // The list owns these nodes; the map only stores non-owning pointers.
    for (auto &a : valNodeMap) {
      a.second = nullptr;
    }
    pthread_mutex_destroy(&mutex);
  }

  int get(int key) {
    // Protect both the lookup and recency-list update as one operation.
    pthread_mutex_lock(&mutex);
    auto it = valNodeMap.find(key);
    if (it == valNodeMap.end()) {
      cout << "[cache] miss key=" << key << endl;
      pthread_mutex_unlock(&mutex);
      return -1;
    }

    NODE *node = it->second;
    // Move the found node to the most-recently-used position.
    NODE *prevNode = nullptr, *nextNode = nullptr;
    prevNode = node->prev;
    nextNode = node->next;

    //remove the 'node'
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    //insert the 'node' at the front;
    NODE *firstNode = HEAD->next;
    HEAD->next = node;
    node->prev = HEAD;
    node->next = firstNode;
    firstNode->prev = node;

    int value = node->val;
    cout << "[cache] hit key=" << key << " value=" << value << endl;
    pthread_mutex_unlock(&mutex);
    return value;
  }

  bool put(int key, int val) {
    // The map and list must stay consistent while inserting, updating,
    // moving, or evicting an entry.
    pthread_mutex_lock(&mutex);

    currSize++;

    if (!valNodeMap.count(key)) {
      //if the key doesnt exist

      //insert the node at the front
      NODE *newNode = new NODE(key, val);
      //insert the 'node' at the front;
      NODE *firstNode = HEAD->next;
      HEAD->next = newNode;
      newNode->prev = HEAD;
      newNode->next = firstNode;
      firstNode->prev = newNode;

      //update the map
      valNodeMap[key] = newNode;
      cout << "[cache] inserted key=" << key << " value=" << val << endl;

    } else {
      //if the key already exists
      NODE *node = valNodeMap[key];
      //delete this node and push it in the front
      NODE *prevNode = nullptr, *nextNode = nullptr;
      prevNode = node->prev;
      nextNode = node->next;

      //remove the 'node'
      prevNode->next = nextNode;
      nextNode->prev = prevNode;
      currSize--;

      //insert the 'node' at the front;
      NODE *firstNode = HEAD->next;
      HEAD->next = node;
      node->prev = HEAD;
      node->next = firstNode;
      firstNode->prev = node;

      //update the val
      node->val = val;
      cout << "[cache] updated key=" << key << " value=" << val << endl;
    }

    // Evict the least-recently-used node if the cache exceeds capacity.
    if (currSize > capacity) {

      NODE *prevNode = TAIL->prev;
      prevNode->prev->next = TAIL;
      TAIL->prev = prevNode->prev;
      prevNode->prev = prevNode->next = nullptr;

      int key = prevNode->key;
      valNodeMap.erase(key);
      cout << "[cache] evicted key=" << key << endl;
      delete (prevNode);
      currSize--;
    }
    pthread_mutex_unlock(&mutex);
    return true;
  }

private:
  NODE *HEAD,
      *TAIL;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  int capacity;
  int currSize;
  unordered_map<int, NODE *> valNodeMap;
};

static void check(const char *name, bool passed, int &failures) {
  cout << (passed ? "PASS: " : "FAIL: ") << name << endl;
  if (!passed) {
    failures++;
  }
}

static void checkGet(LRUCache &cache, int key, int expected,
                     const char *name, int &failures) {
  int actual = cache.get(key);
  cout << "  expected " << expected << ", got " << actual << endl;
  check(name, actual == expected, failures);
}

struct ThreadArgs {
  LRUCache *cache;
  int threadId;
  int failures;
};

static void *cacheWorker(void *arg) {
  ThreadArgs *args = static_cast<ThreadArgs *>(arg);
  const int iterations = 1000;
  const int keyCount = 4;

  printf("[worker %d] started\n", args->threadId);
  for (int i = 0; i < iterations; ++i) {
    for (int key = 0; key < keyCount; ++key) {
      int value = key * 10;
      if (!args->cache->put(key, value)) {
        fprintf(stderr, "[worker %d] put failed: key=%d iteration=%d\n",
                args->threadId, key, i);
        args->failures++;
      }

      int actual = args->cache->get(key);
      if (actual != value) {
        fprintf(stderr,
                "[worker %d] value mismatch: key=%d expected=%d actual=%d "
                "iteration=%d\n",
                args->threadId, key, value, actual, i);
        args->failures++;
      }
    }
  }

  printf("[worker %d] finished with %d failure(s)\n",
         args->threadId, args->failures);
  return nullptr;
}

int main() {
  int failures = 0;
  const int threadCount = 4;
  const int keyCount = 4;
  LRUCache concurrentCache(keyCount);
  pthread_t threads[threadCount];
  ThreadArgs args[threadCount];
  int createdThreads = 0;

  for (int i = 0; i < threadCount; ++i) {
    args[i] = {&concurrentCache, i, 0};
    cout << "[main] starting worker " << i << endl;
    int rc = pthread_create(&threads[i], nullptr, cacheWorker, &args[i]);
    if (rc != 0) {
      cerr << "pthread_create failed with error " << rc << endl;
      break;
    }
    createdThreads++;
  }

  bool allThreadsJoined = true;
  for (int i = 0; i < createdThreads; ++i) {
    cout << "[main] joining worker " << i << endl;
    int rc = pthread_join(threads[i], nullptr);
    if (rc != 0) {
      cerr << "pthread_join failed with error " << rc << endl;
      failures++;
      allThreadsJoined = false;
    }
  }

  // Only inspect or destroy the shared cache after all workers have stopped.
  if (createdThreads == threadCount && allThreadsJoined) {
    int workerFailures = 0;
    for (int i = 0; i < threadCount; ++i) {
      workerFailures += args[i].failures;
    }
    check("concurrent get/put operations", workerFailures == 0, failures);

    for (int key = 0; key < keyCount; ++key) {
      checkGet(concurrentCache, key, key * 10,
               "concurrent cache retains expected value", failures);
    }
  } else if (createdThreads != threadCount) {
    check("create all worker threads", false, failures);
  }

  cout << (failures == 0 ? "All tests passed." : "Some tests failed.")
       << endl;
  return failures == 0 ? 0 : 1;
}