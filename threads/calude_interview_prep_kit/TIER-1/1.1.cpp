
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>

using namespace std;

#define N 5
int shared_counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/*void *thread_func(void *args) {
  // in this mechanism lock/unlock happens 100000 times for each thread - slow
  for (int i = 0; i < 1000000; i++) {
    pthread_mutex_lock(&mtx);
    shared_counter++;
    pthread_mutex_unlock(&mtx);
  }
  // cout << "THREAD: " << pthread_self() << " shared_counter :" << shared_counter << endl;

  return nullptr;
}*/

void *thread_func(void *args) {

  int local_counter = 0; // this is local variable to each thread
  for (int i = 0; i < 1000000; i++) {

    local_counter++;
  }
  pthread_mutex_lock(&mtx);
  shared_counter += local_counter;
  pthread_mutex_unlock(&mtx);

  // cout << "THREAD: " << pthread_self() << " shared_counter :" << shared_counter << endl;

  return nullptr;
}

int main() {

  vector<pthread_t> threads(N, 0);
  // initialize the mutex

  // create N threads
  for (int i = 0; i < N; i++) {

    pthread_create(&threads[i], nullptr, thread_func, nullptr);
  }

  // join the threads
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], nullptr);
  }
  cout << "shared_counter:" << shared_counter << endl;

  return 0;
}
