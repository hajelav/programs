#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
int go = 0;

typedef struct {
  int id;
} WaiterArgs;

void *waiter(void *arg) {
  WaiterArgs *wa = (WaiterArgs *)arg;

  pthread_mutex_lock(&mtx);
  printf("waiter %d: sleeping\n", wa->id);

  while (!go) {
    pthread_cond_wait(&cv, &mtx);
  }

  printf("waiter %d: woke up and proceeding\n", wa->id);

  pthread_mutex_unlock(&mtx);
  return NULL;
}

int main() {
  pthread_t threads[3];
  WaiterArgs args[3];

  for (int i = 0; i < 3; ++i) {
    args[i].id = i;
    pthread_create(&threads[i], NULL, waiter, &args[i]);
  }

  sleep(1);
  printf("main: calling pthread_cond_signal -- expect only ONE waiter to wake\n");

  pthread_mutex_lock(&mtx);
  go = 1;
  pthread_cond_signal(&cv);
  pthread_mutex_unlock(&mtx);

  sleep(1);
  printf("main: calling pthread_cond_broadcast -- expect ALL waiters to wake\n");

  pthread_mutex_lock(&mtx);
  go = 1;
  pthread_cond_broadcast(&cv);
  pthread_mutex_unlock(&mtx);

  for (int i = 0; i < 3; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}