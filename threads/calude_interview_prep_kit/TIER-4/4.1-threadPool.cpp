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

using namespace std;

typedef struct task {
  void (*cb)(void *);
  void *args;
} TASK;

class ThreadPool {

public:
  ThreadPool(int capacity, int noOfThreads)
      : capacity(capacity) {
    mtx = PTHREAD_MUTEX_INITIALIZER;
    full = PTHREAD_COND_INITIALIZER;
    empty = PTHREAD_COND_INITIALIZER;

    //create worker threads
  }

  void push(TASK *task) {

    /* producer thread operates here*/
    pthread_mutex_lock(&mtx);
    //we have to wait if the queue is full
    while (buffer.size() >= capacity) {
      pthread_cond_wait(&full, &mtx);
    }
    //push the task into the q
    buffer.push_front(task);
    //signal the consumer
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mtx);
  }

  /*consumer thread operates here*/
  void worker() {
    pthread_mutex_lock(&mtx);

    //wait till there is atleast one task to be consumed in the buffer
    while (buffer.size() <= 0) {
      pthread_cond_wait(&empty, &mtx);
    }
    //consume the item
    TASK *task = buffer.back();
    //call the task
    task->cb(task->args);
    buffer.pop_back();
    //signal the producer to produce the item
    pthread_cond_signal(&full);

    pthread_mutex_unlock(&mtx);
  }

private:
  pthread_mutex_t mtx;
  pthread_cond_t full;
  pthread_cond_t empty;
  deque<TASK *> buffer;
  vector<pthread_t> workers;
  int capacity;
};

/* producer thread*/
void *producer(void* args) {
}

/*consumer thread*/
void consumer(void* args) {

}

int main() {

  return 0;
}