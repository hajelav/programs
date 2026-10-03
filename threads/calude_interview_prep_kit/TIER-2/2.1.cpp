#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <deque>
#include <iostream>

using namespace std;

class ProducerConsumer {

public:
  ProducerConsumer(int size)
      : capacity(size) {
    mtx = PTHREAD_MUTEX_INITIALIZER;
    empty = PTHREAD_COND_INITIALIZER;
    full = PTHREAD_COND_INITIALIZER;
  }

  void push(int val) {
    pthread_mutex_lock(&mtx);
    while (buffer.size() >= static_cast<long unsigned int>(capacity)) {
      pthread_cond_wait(&full, &mtx);
    }
    //push the element
    cout << "Thread Id:" << pthread_self() << " Pushing value :" << val << endl;
    buffer.push_back(val);
    //signal the consumer thread
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mtx);
  }

  void pop() {
    pthread_mutex_lock(&mtx);
    while (buffer.empty()) {
      pthread_cond_wait(&empty, &mtx);
    }
    cout << "Thread Id:" << pthread_self() << " Consuming  value :" << buffer.front() << endl;
    //push the element
    buffer.pop_front();
    //signal the consumer thread
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mtx);
  }

private:
  deque<int> buffer;
  int capacity;

  pthread_mutex_t mtx;
  pthread_cond_t empty, full;
};

/*typedef struct work {
  ProducerConsumer *task;
  int val;
  work(ProducerConsumer *pc, int v)
      : task(pc), val(v) {}
} WORK;*/

//producer thread
static void *producer(void *args) {

  while (1) {
    //produce a random number
    sleep(1);
    int val = rand() % 100;
    ProducerConsumer *pc = static_cast<ProducerConsumer *>(args);
    pc->push(val);
  }

  return nullptr;
}

//consumer thread
static void *consumer(void *args) {
  while (1) {
    //consume a random number
    sleep(1);
    ProducerConsumer *pc = static_cast<ProducerConsumer *>(args);
    pc->pop();
  }
  return nullptr;
}
int main() {
  int producerCount = 3;
  int consumerCount = 1;
  vector<pthread_t> producerTid;
  vector<pthread_t> consumerTid;

  for (int i = 0; i < producerCount; i++) {
    producerTid.push_back(0);
  }
  for (int i = 0; i < consumerCount; i++) {
    consumerTid.push_back(0);
  }

  //create a producer-consume class with capacity as X
  ProducerConsumer *PC = new ProducerConsumer(3);

  // create producer and consumer threads before waiting on them
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