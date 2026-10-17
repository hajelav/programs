#include <pthread.h> // pthread API
#include <stdio.h>   // standard I/O
#include <time.h>    // sleep
#include <errno.h>   // error codes
#include <unistd.h>  // POSIX functions
#include <vector>    // vector
#include <deque>     // queue
#include <iostream>  // cout
#include <queue>
#include <unordered_map>

#define NO_OF_ITEMS 20
using namespace std;
class ThreadPool;
//void *thread_func(void *args);

typedef void (*CALLBACK)(void *);
typedef struct task {
  CALLBACK cb;
  void *args;
  task(CALLBACK cb, void *args)
      : cb(cb), args(args) {}
} TASK;

class ThreadPool {

public:
  ThreadPool(int capacity, int noOfThreads)
      : capacity(capacity), noOfThreads(noOfThreads), shutdown(false) {
    mtx = PTHREAD_MUTEX_INITIALIZER;
    full = PTHREAD_COND_INITIALIZER;
    empty = PTHREAD_COND_INITIALIZER;
    workers.resize(noOfThreads);
    cout << "[main] Creating thread pool with capacity=" << capacity
         << " and threads=" << noOfThreads << endl;

    //create worker threads
    for (int i = 0; i < noOfThreads; i++) {
      pthread_create(&workers[i], nullptr, ThreadPool::thread_func, this);
      cout << "[main] Worker thread " << i << " started" << endl;
    }
  }

  ~ThreadPool() {
    shutdownThreadPool();
  }

  void shutdownThreadPool() {
    pthread_mutex_lock(&mtx);
    shutdown = true;
    pthread_cond_broadcast(&empty);
    pthread_cond_broadcast(&full);
    pthread_mutex_unlock(&mtx);

    for (int i = 0; i < noOfThreads; i++) {
      pthread_join(workers[i], nullptr);
    }
  }

  void push(TASK *task) {

    /* producer thread operates here*/
    pthread_mutex_lock(&mtx);
    cout << "[push] Waiting for space in queue" << endl;
    while (shutdown) {
      pthread_mutex_unlock(&mtx);
      return;
    }
    //we have to wait if the queue is full
    while ((int)buffer.size() >= capacity && !shutdown) {
      pthread_cond_wait(&full, &mtx);
    }
    if (shutdown) {
      pthread_mutex_unlock(&mtx);
      delete task;
      return;
    }
    //push the task into the q
    buffer.push_front(task);
    cout << "[push] Added task to queue. Current size=" << buffer.size() << endl;
    //signal the consumer
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mtx);
  }

  /*consumer thread operates here*/
  void worker() {
    pthread_mutex_lock(&mtx);

    cout << "[worker] Waiting for task" << endl;
    while (buffer.size() <= 0 && !shutdown) {
      pthread_cond_wait(&empty, &mtx);
    }

    if (shutdown && buffer.empty()) {
      pthread_mutex_unlock(&mtx);
      cout << "[worker] Shutting down" << endl;
      pthread_exit(nullptr);
    }

    //consume the item
    TASK *task = buffer.back();
    cout << "[worker] Picked a task from queue. Remaining=" << buffer.size() - 1 << endl;
    buffer.pop_back();
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mtx);

    //call the task outside the lock
    task->cb(task->args);
    cout << "[worker] Completed task. Queue size now=" << buffer.size() << endl;
    delete task;
  }

  static void *thread_func(void *args) {
    ThreadPool *tp = static_cast<ThreadPool *>(args);
    cout << "[thread_func] Worker thread started" << endl;
    while (1) {
      tp->worker();
    }
    return nullptr;
  }

private:
  pthread_mutex_t mtx;
  pthread_cond_t full;
  pthread_cond_t empty;
  deque<TASK *> buffer;
  vector<pthread_t> workers;
  int capacity;
  int noOfThreads;
  bool shutdown;
};

void print_task(void *args) {
  int *p = static_cast<int *>(args);
  cout << "[task] print_task value=" << *p << endl;
  delete p;
}

int main() {
  ThreadPool *tp = new ThreadPool(10, 5);
  cout << "[main] Producing tasks" << endl;
  //main thread produces
  for (int i = 0; i < NO_OF_ITEMS; i++) {
    int *p = new int(i);
    TASK *task = new TASK(print_task, p);
    cout << "[main] Enqueuing task with value=" << i << endl;
    tp->push(task);
  }
  cout << "[main] Done producing tasks" << endl;

  delete tp;
  return 0;
}