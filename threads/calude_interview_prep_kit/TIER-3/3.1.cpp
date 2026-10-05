#include <pthread.h> // pthread API
#include <stdio.h>   // standard I/O
#include <time.h>    // sleep
#include <errno.h>   // error codes
#include <unistd.h>  // POSIX functions
#include <vector>    // vector
#include <deque>     // queue
#include <iostream>  // cout
#include <queue>

using namespace std;

/* Timer implementation using priority queue*/

typedef void (*CALLBACK)(void);

static struct timespec getRemainingTime(const struct timespec &now, const struct timespec &expiry) {
  struct timespec remaining;
  remaining.tv_sec = expiry.tv_sec - now.tv_sec;
  remaining.tv_nsec = 0;
  return remaining;
}

/* Step 1 : create a Timer TASK*/
typedef struct task {
  struct timespec expiration_time; // absolute time when this task should run
  CALLBACK cb;                     // callback function registered by caller
  bool is_cancelled;               // if the task is cancelled by caller
  int period;                      // if > 0, task is periodic; else it is a one-shot task
  task(struct timespec ts, CALLBACK c, bool is_cancelled, int period)
      : expiration_time(ts), cb(c), is_cancelled(is_cancelled), period(period) {}
} TASK;

class TimerMgr {

public:
  struct comp {
    bool operator()(TASK *t1, TASK *t2) {
      // priority queue returns the smallest expiry time at the top
      return t1->expiration_time.tv_sec > t2->expiration_time.tv_sec;
    }
  };

  TimerMgr() {
    mtx = PTHREAD_MUTEX_INITIALIZER;
    cv = PTHREAD_COND_INITIALIZER;
  }

  void insert(TASK *task) {
    pthread_mutex_lock(&mtx);
    cout << "[insert] Adding task with expiry " << task->expiration_time.tv_sec << " sec" << endl;
    // push the task in the priority queue; earliest expiry is processed first
    minPQ.push(task);
    cout << "[insert] Queue size after push: " << minPQ.size() << endl;
    // wake the worker thread if it is sleeping
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&mtx);
  }

  void worker() {
    pthread_mutex_lock(&mtx);

    while (minPQ.empty()) {
      cout << "[worker] Queue empty, waiting..." << endl;
      pthread_cond_wait(&cv, &mtx);
    }

    TASK *frontTask = minPQ.top();
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);

    // if the earliest task has not expired yet, wait for the remaining time
    while (now.tv_sec < frontTask->expiration_time.tv_sec) {
      struct timespec remaining = getRemainingTime(now, frontTask->expiration_time);
      //cout << "[worker] Waiting for " << remaining.tv_sec << " sec" << endl;
      pthread_cond_timedwait(&cv, &mtx, &remaining);
      clock_gettime(CLOCK_REALTIME, &now);
    }

    cout << "[worker] Executing callback now" << endl;
    frontTask->cb();

    // periodic tasks can be reinserted by updating expiration_time and pushing back
    // one-shot tasks are simply removed after execution
    if (frontTask->period) {
      struct timespec pTime;
      pTime.tv_sec = frontTask->expiration_time.tv_sec + frontTask->period;
      minPQ.pop();
      frontTask->expiration_time = pTime;
      minPQ.push(frontTask);
      cout << "[worker] Reinserted periodic task" << endl;
    } else {
      minPQ.pop();
      cout << "[worker] Removed task" << endl;
    }

    pthread_mutex_unlock(&mtx);
  }

private:
  priority_queue<TASK *, vector<TASK *>, comp> minPQ;
  pthread_mutex_t mtx;
  pthread_cond_t cv;
};

void user_function() {
  cout << "[callback] user function called, value = " << (rand() % 10) << endl;
}

//producer thread
void *producer_thread(void *args) {

  TimerMgr *mgr = static_cast<TimerMgr *>(args);
  //keep pushing task into the producer thread
  while (1) {
    // get a random delay between 1-5 secs
    int delay = (rand() % 5) + 1;
    struct timespec currTime;
    clock_gettime(CLOCK_REALTIME, &currTime);
    currTime.tv_sec += delay;
    cout << "[producer] Creating task with delay " << delay << " sec" << endl;
    // assign function pointer (do not call)
    CALLBACK cb = user_function;
    //TASK *task = new TASK(currTime, cb, false, 0); // one shot timers
    TASK *task = new TASK(currTime, cb, false, 5); // periodic timers
    //push the task onto the queue
    mgr->insert(task);
    sleep(1);
  }

  return nullptr;
}

void *consumer_thread(void *args) {

  TimerMgr *mgr = static_cast<TimerMgr *>(args);
  while (1) {
    cout << "[consumer] Calling worker()" << endl;
    mgr->worker();
  }
}

int main() {

  pthread_t pThread, cThread;
  TimerMgr *mgr = new TimerMgr();
  /* two thread model
  1. one producer pushing the tasks
  2. one consumer processing the tasks
  */
  cout << "[main] Starting timer threads" << endl;
  pthread_create(&pThread, nullptr, producer_thread, static_cast<void *>(mgr));
  pthread_create(&cThread, nullptr, consumer_thread, static_cast<void *>(mgr));

  cout << "[main] Waiting for producer and consumer threads" << endl;
  pthread_join(pThread, nullptr);
  pthread_join(cThread, nullptr);

  return 0;
}