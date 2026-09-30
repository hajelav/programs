
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>

using namespace std;

#define N 5
int shared_counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *args) {
  pthread_mutex_lock(&mtx);
  for (int i = 0; i < 1000000; i++) {

    shared_counter++;
  }
  cout << "THREAD: " << pthread_self() << " shared_counter :" << shared_counter << endl;
  pthread_mutex_unlock(&mtx);
  return nullptr;
}

int main() {

  vector<pthread_t> threads(N, 0);
  // initialize the mutex

  // create N threads
  for (int i = 0; i < N; i++) {

    pthread_create(&threads[i], nullptr, thread_func, nullptr);
  }

  // cout << "shared_counter:" << shared_counter << endl;

  // join the threads
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], nullptr);
  }

  return 0;
}
