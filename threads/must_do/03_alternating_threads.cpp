
/* using condition variables */
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

int turn = 1; // defines the turn of the thread, start with turn of thread1
#define N 2

void *thread1_func(void *args) {

  while (1) {
    pthread_mutex_lock(&mtx);
    while (turn != 1) {
      pthread_cond_wait(&cv, &mtx);
    }
    cout << "Thread Id : " << pthread_self() << " Thread 1's turn" << endl;
    // set the turn
    turn = 2;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&mtx);
    sleep(1);
  }
  return nullptr;
}

void *thread2_func(void *args) {

  while (1) {
    pthread_mutex_lock(&mtx);
    while (turn != 2) {
      pthread_cond_wait(&cv, &mtx);
    }
    cout << "Thread Id : " << pthread_self() << " Thread 2's turn" << endl;
    // set the turn
    turn = 1;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&mtx);
    sleep(1);
  }
  return nullptr;
}

int main() {

  vector<pthread_t> tid(2, 0);

  // create 2 threads

  pthread_create(&tid[0], nullptr, thread1_func, nullptr);
  pthread_create(&tid[1], nullptr, thread2_func, nullptr);

  // join the threads
  for (int i = 0; i < N; i++) {
    pthread_join(tid[i], nullptr);
  }
}
