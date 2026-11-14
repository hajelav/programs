
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

    // HEAD and TAIL are sentinels. Real entries are linked between them,
    // with the most recently used entry nearest HEAD.
    HEAD = new NODE(-1, -1); // insertion from head(most recent)
    TAIL = new NODE(-1, -1); // deletion from tail (least recent)
    HEAD->next = TAIL;
    TAIL->prev = HEAD;
    cout << "[cache] created with capacity=" << capacity << endl;
  }

  ~LRUCache() {
    // Save each previous pointer before deleting the current list node.
    // The map stores non-owning pointers, so the list owns and deletes nodes.
    cout << "[cache] destroying; entries=" << currSize << endl;
    NODE *currNode = nullptr;
    currNode = TAIL;
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

    for (auto &a : valNodeMap) {
      a.second = nullptr;
    }
  }

  int get(int key) {
    cout << "[cache] get key=" << key << endl;
    if (!valNodeMap.count(key)) {
      cout << "key :" << key << " not found" << endl;
      return -1;
    }

    NODE *node = valNodeMap[key];
    cout << "[cache] hit key=" << key << " value=" << node->val << endl;
    // Unlink this node from its current position before moving it to the front.
    NODE *prevNode = nullptr, *nextNode = nullptr;
    prevNode = node->prev;
    nextNode = node->next;

    // Bridge the previous and next nodes to remove this node from the list.
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    // Insert immediately after HEAD to mark this entry as most recently used.
    NODE *firstNode = HEAD->next;
    HEAD->next = node;
    node->prev = HEAD;
    node->next = firstNode;
    firstNode->prev = node;

    return node->val;
  }

  bool put(int key, int val) {

    cout << "[cache] put key=" << key << " value=" << val << endl;
    currSize++;

    if (!valNodeMap.count(key)) {
      // A new key gets a node at the most-recently-used end of the list.
      NODE *newNode = new NODE(key, val);
      NODE *firstNode = HEAD->next;
      HEAD->next = newNode;
      newNode->prev = HEAD;
      newNode->next = firstNode;
      firstNode->prev = newNode;

      // Keep the map pointing at the node owned by the linked list.
      valNodeMap[key] = newNode;
      cout << "[cache] inserted key=" << key
           << "; size=" << currSize << endl;

    } else {
      // Updating an existing key does not add another cache entry.
      NODE *node = valNodeMap[key];
      NODE *prevNode = nullptr, *nextNode = nullptr;
      prevNode = node->prev;
      nextNode = node->next;

      // Unlink the existing node, then move it to the most-recent end.
      prevNode->next = nextNode;
      nextNode->prev = prevNode;
      currSize--;

      NODE *firstNode = HEAD->next;
      HEAD->next = node;
      node->prev = HEAD;
      node->next = firstNode;
      firstNode->prev = node;

      node->val = val;
      cout << "[cache] updated key=" << key
           << "; size=" << currSize << endl;
    }

    // If over capacity, the node immediately before TAIL is least recently used.
    if (currSize > capacity) {

      NODE *prevNode = TAIL->prev;
      prevNode->prev->next = TAIL;
      TAIL->prev = prevNode->prev;
      prevNode->prev = prevNode->next = nullptr;

      int key = prevNode->key;
      valNodeMap.erase(key);
      cout << "[cache] evicting least-recently-used key=" << key << endl;
      delete (prevNode);
      currSize--;
    }
    cout << "[cache] put complete; size=" << currSize << endl;
    return true;
  }

private:
  NODE *HEAD,
      *TAIL;
  int capacity;
  int currSize;
  unordered_map<int, NODE *> valNodeMap;
};

static void check(const char *name, bool passed, int &failures) {
  cout << "[test] " << name << endl;
  cout << (passed ? "PASS: " : "FAIL: ") << name << endl;
  if (!passed) {
    failures++;
  }
}

static void checkGet(LRUCache &cache, int key, int expected,
                     const char *name, int &failures) {
  cout << "[test] checking get(" << key << ")" << endl;
  int actual = cache.get(key);
  cout << "  expected " << expected << ", got " << actual << endl;
  check(name, actual == expected, failures);
}

int main() {
  int failures = 0;
  cout << "[test] starting LRU cache behavior checks" << endl;
  LRUCache cache(2);

  cout << "[test] insert two entries, then access key 1 to make it recent"
       << endl;
  check("insert key 1", cache.put(1, 10), failures);
  check("insert key 2", cache.put(2, 20), failures);
  checkGet(cache, 1, 10, "get key 1", failures);

  cout << "[test] insert key 3; key 2 should now be least-recent and evicted"
       << endl;
  check("insert key 3 and evict least-recent key 2",
        cache.put(3, 30), failures);
  checkGet(cache, 2, -1, "key 2 was evicted", failures);
  checkGet(cache, 1, 10, "key 1 remains", failures);
  checkGet(cache, 3, 30, "key 3 remains", failures);

  cout << "[test] update key 1; an update should not evict key 3" << endl;
  check("update key 1", cache.put(1, 11), failures);
  checkGet(cache, 1, 11, "updated value is returned", failures);
  checkGet(cache, 3, 30, "updating key 1 did not evict key 3", failures);

  cout << "[test] insert key 4; key 1 should be evicted after recent accesses"
       << endl;
  check("insert key 4 and evict least-recent key 1",
        cache.put(4, 40), failures);
  checkGet(cache, 1, -1, "key 1 was evicted", failures);
  checkGet(cache, 4, 40, "key 4 remains", failures);

  cout << (failures == 0 ? "All tests passed." : "Some tests failed.")
       << endl;
  return failures == 0 ? 0 : 1;
}