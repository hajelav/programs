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
      : capacity(capacity) {
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
    //join the threads
    for (int i = 0; i < noOfThreads; i++) {
      pthread_join(workers[i], nullptr);
    }
  }

  void push(TASK *task) {

    /* producer thread operates here*/
    pthread_mutex_lock(&mtx);
    cout << "[push] Waiting for space in queue" << endl;
    //we have to wait if the queue is full
    while ((int)buffer.size() >= capacity) {
      pthread_cond_wait(&full, &mtx);
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
    //wait till there is atleast one task to be consumed in the buffer
    while (buffer.size() <= 0) {
      pthread_cond_wait(&empty, &mtx);
    }
    //consume the item
    TASK *task = buffer.back();
    cout << "[worker] Picked a task from queue. Remaining=" << buffer.size() - 1 << endl;
    //call the task
    task->cb(task->args);
    buffer.pop_back();
    cout << "[worker] Completed task. Queue size now=" << buffer.size() << endl;
    //signal the producer to produce the item
    pthread_cond_signal(&full);

    pthread_mutex_unlock(&mtx);
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
  return 0;
}