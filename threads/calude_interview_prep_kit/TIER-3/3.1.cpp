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

/* Step 1 : create a Timer TASK*/
typedef struct task {
  time_t expiration_time;
  CALLBACK cb;
  bool is_cancelled;
  int peroid;
} TASK;

class TimerMgr {

public:
  struct comp {
    bool operator()(TASK *t1, TASK *t2) {
      return t1->expiration_time >= t2->expiration_time;
    }
  };

  TimerMgr() {
    mtx = PTHREAD_MUTEX_INITIALIZER;
    cv = PTHREAD_COND_INITIALIZER;
  }

  void insert(TASK *task) {
    //inserts the element into the minPQ --> done by producer thread
    pthread_mutex_lock(&mtx);
    minPQ.push(task);
    pthread_mutex_unlock(&mtx);
  }

  void worker() {
    //processing done by consumer thread
  }

private:
  priority_queue<TASK *, vector<TASK *>, comp> minPQ;
  pthread_mutex_t mtx;
  pthread_cond_t cv;
};

int main() {

  return 0;
}