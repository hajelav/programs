#include <pthread.h> // pthread API
#include <stdio.h>   // standard I/O
#include <time.h>    // sleep
#include <errno.h>   // error codes
#include <unistd.h>  // POSIX functions
#include <vector>    // vector
#include <deque>     // queue
#include <iostream>  // cout

using namespace std;

// Producer-consumer queue with mutex and condition variables
class ProducerConsumer {

public:
  // Initializes the buffer and synchronization objects.
  ProducerConsumer(int size)
      : capacity(size) {
    mtx = PTHREAD_MUTEX_INITIALIZER;
    empty = PTHREAD_COND_INITIALIZER;
    full = PTHREAD_COND_INITIALIZER;
  }

  // Adds an item to the buffer.
  void push(int val) {
    pthread_mutex_lock(&mtx);
    while (buffer.size() >= static_cast<long unsigned int>(capacity)) {
      pthread_cond_wait(&full, &mtx);
    }
    cout << "Thread Id:" << pthread_self() << " Pushing value :" << val << endl;
    buffer.push_back(val);
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mtx);
  }

  // Removes an item from the buffer.
  void pop() {
    pthread_mutex_lock(&mtx);
    while (buffer.empty()) {
      pthread_cond_wait(&empty, &mtx);
    }
    cout << "Thread Id:" << pthread_self() << " Consuming  value :" << buffer.front() << endl;
    buffer.pop_front();
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mtx);
  }

private:
  deque<int> buffer;
  int capacity;

  pthread_mutex_t mtx;
  pthread_cond_t empty, full;
};

/*
  Example of alternative thread parameter structure.
  Not used here.
*/

// Producer thread
static void *producer(void *args) {

  while (1) {
    sleep(1);
    int val = rand() % 100;
    ProducerConsumer *pc = static_cast<ProducerConsumer *>(args);
    pc->push(val);
  }

  return nullptr;
}

// Consumer thread
static void *consumer(void *args) {
  while (1) {
    sleep(1);
    ProducerConsumer *pc = static_cast<ProducerConsumer *>(args);
    pc->pop();
  }
  return nullptr;
}

int main() {
  int producerCount = 10; // number of producers
  int consumerCount = 5;  // number of consumers
  vector<pthread_t> producerTid;
  vector<pthread_t> consumerTid;

  for (int i = 0; i < producerCount; i++) {
    producerTid.push_back(0);
  }
  for (int i = 0; i < consumerCount; i++) {
    consumerTid.push_back(0);
  }

  ProducerConsumer *PC = new ProducerConsumer(3);

  for (int i = 0; i < producerCount; i++) {
    pthread_create(&producerTid[i], nullptr, producer, static_cast<void *>(PC));
  }
  for (int i = 0; i < consumerCount; i++) {
    pthread_create(&consumerTid[i], nullptr, consumer, static_cast<void *>(PC));
  }

  for (int i = 0; i < producerCount; i++) {
    pthread_join(producerTid[i], nullptr);
  }
  for (int i = 0; i < consumerCount; i++) {
    pthread_join(consumerTid[i], nullptr);
  }
}