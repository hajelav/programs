#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
int flag = 0;
void *waiter_with_timeout(void *arg) {

  struct timespec deadline;
  clock_gettime(CLOCK_REALTIME, &deadline); /* get "now" */
  deadline.tv_sec += 2;                     /* "now" + 2s -- ABSOLUTE time, not a duration */
  pthread_mutex_lock(&mtx);
  int rc = 0;
  while (!flag && rc != ETIMEDOUT) {
    rc = pthread_cond_timedwait(&cv, &mtx, &deadline);
  }
  if (rc == ETIMEDOUT) {
    printf("waiter: gave up after timeout, flag is still %d\n", flag);
  } else {
    printf("waiter: woke up because flag became %d\n", flag);
  }
  pthread_mutex_unlock(&mtx);
  return NULL;
}

void *waiter(void *args) {
  /* this thread sleeps for 1 sec and send the signal to other thread, testing the condition when the other thread wakes up before timeout*/
  pthread_mutex_lock(&mtx);
  sleep(1);
  flag = 1;
  pthread_cond_signal(&cv);
  pthread_mutex_unlock(&mtx);
  return nullptr;
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, waiter_with_timeout, NULL);
  /* Don't set flag at all -- let the 2-second timeout fire, to see the ETIMEDOUT path. */

  pthread_create(&t2, NULL, waiter, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
