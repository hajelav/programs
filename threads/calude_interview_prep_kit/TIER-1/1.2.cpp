
/*passing arguments to the thread function*/

#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>

using namespace std;

#define N 5
int shared_counter = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct args {
  int id;
  args(int i) : id(i) {}
} ARGS;

void *thread_func(void *args) {
  // cast the arguments

  ARGS *arg = static_cast<ARGS *>(args);
  pthread_mutex_lock(&mtx);
  cout << "Thread Id : " << pthread_self() << " id :" << arg->id << endl;

  pthread_mutex_unlock(&mtx);
  delete(arg);
  return nullptr;
}

int main() {

  vector<pthread_t> threads(N, 0);
  // initialize the mutex

  // create N threads
  for (int i = 0; i < N; i++) {

    ARGS *arg = new ARGS(i);
    pthread_create(&threads[i], nullptr, thread_func, static_cast<void *>(arg));
  }

  // join the threads
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], nullptr);
  }
  cout << "shared_counter:" << shared_counter << endl;

  return 0;
}
