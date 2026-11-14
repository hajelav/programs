/* Implement the readers-writers problem using pthreads, mutexes, and condition variables.*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
class ReadersWriters {
public:
  ReadersWriters()
      : readCount(0), isWriting(false) {
    // One mutex protects the shared reader count and writer state.
    cout << "[rw] synchronization objects initialized" << endl;
  }

  ~ReadersWriters() {
    // The caller must stop and join all users before destroying these objects.
    cout << "[rw] destroying synchronization objects" << endl;
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&readLock);
    pthread_cond_destroy(&writeLock);
  }

  void reader(int id) {
    // Readers share the resource, but cannot enter during a writer's turn.
    pthread_mutex_lock(&mutex);
    while (isWriting) {
      cout << "[reader " << id << "] waiting: a writer is active" << endl;
      pthread_cond_wait(&readLock, &mutex);
    }
    ++readCount;
    cout << "[reader " << id << "] entering; active readers=" << readCount
         << endl;
    pthread_mutex_unlock(&mutex);

    cout << "Reader " << id << " is reading." << endl;
    sleep(1);

    pthread_mutex_lock(&mutex);
    --readCount;
    cout << "[reader " << id << "] leaving; active readers=" << readCount
         << endl;
    if (readCount == 0) {
      cout << "[reader " << id << "] last reader leaving; signaling a writer"
           << endl;
      pthread_cond_signal(&writeLock);
    }
    pthread_mutex_unlock(&mutex);
  }

  void writer(int id) {
    // A writer needs exclusive access: no active writer or reader may remain.
    pthread_mutex_lock(&mutex);
    while (isWriting || readCount > 0) {
      cout << "[writer " << id << "] waiting; active readers=" << readCount
           << ", writer active=" << isWriting << endl;
      pthread_cond_wait(&writeLock, &mutex);
    }
    isWriting = true;
    cout << "[writer " << id << "] entering" << endl;
    pthread_mutex_unlock(&mutex);

    cout << "Writer " << id << " is writing." << endl;
    sleep(1);

    pthread_mutex_lock(&mutex);
    isWriting = false;
    cout << "[writer " << id << "] leaving; waking waiting readers" << endl;
    pthread_cond_broadcast(&readLock);
    pthread_mutex_unlock(&mutex);
  }

private:
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t readLock = PTHREAD_COND_INITIALIZER;
  pthread_cond_t writeLock = PTHREAD_COND_INITIALIZER;
  int readCount;
  bool isWriting;
};

void *readerTask(void *arg) {
  pair<ReadersWriters *, int> *data = static_cast<pair<ReadersWriters *, int> *>(arg);
  cout << "[reader thread " << data->second << "] started" << endl;
  while (true) {
    data->first->reader(data->second);
    sleep(1);
  }
  return nullptr;
}

void *writerTask(void *arg) {
  pair<ReadersWriters *, int> *data = static_cast<pair<ReadersWriters *, int> *>(arg);
  cout << "[writer thread " << data->second << "] started" << endl;
  while (true) {
    data->first->writer(data->second);
    sleep(2);
  }
  return nullptr;
}

int main() {
  cout << "[main] starting readers-writers demonstration" << endl;
  ReadersWriters rw;
  pthread_t readers[5], writers[2];

  for (int i = 0; i < 5; ++i) {
    cout << "[main] creating reader " << i << endl;
    pthread_create(&readers[i], nullptr, readerTask, new pair<ReadersWriters *, int>(&rw, i));
  }

  for (int i = 0; i < 2; ++i) {
    cout << "[main] creating writer " << i << endl;
    pthread_create(&writers[i], nullptr, writerTask, new pair<ReadersWriters *, int>(&rw, i));
  }

  for (int i = 0; i < 5; ++i) {
    pthread_join(readers[i], nullptr);
  }

  for (int i = 0; i < 2; ++i) {
    pthread_join(writers[i], nullptr);
  }

  return 0;
}
