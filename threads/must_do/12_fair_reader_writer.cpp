/*
  FIFO readers-writers lock: high-level flow

  State:
  - nextTicket gives each arriving reader or writer a unique place in line.
  - servingTicket is the next request allowed to start.
  - readCount tracks readers currently inside; isWriting tracks an active writer.
  - The mutex protects all four variables. Waiters sleep on stateChanged and
    always re-check their conditions in a while loop after waking.

  Reader flow:
  1. Lock the mutex and take a ticket.
  2. Wait until this ticket is being served and no writer is active.
  3. Increment readCount and servingTicket, then wake waiters. Advancing the
     ticket at reader entry allows later consecutive readers to join this
     reader group, so readers can read concurrently.
  4. Unlock the mutex and do the read.
  5. Lock again and decrement readCount. If this was the last reader, wake
     waiters so the next request (possibly a writer) can proceed.

  Writer flow:
  1. Lock the mutex and take a ticket.
  2. Wait until this ticket is being served, there are no active readers, and
     no other writer is active.
  3. Set isWriting, unlock the mutex, and do the write exclusively. Keep
     servingTicket unchanged while writing so later requests cannot pass.
  4. Lock again, clear isWriting, advance servingTicket, and wake waiters.

  main() creates reader and writer threads. Each loops forever, so this demo
  runs continuously and its joins do not normally return.
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
class ReadersWriters {
public:
  ReadersWriters()
      : readCount(0), isWriting(false), nextTicket(0), servingTicket(0) {
    // The mutex protects ticket assignment and every shared state variable.
    cout << "[rw] synchronization objects initialized" << endl;
  }

  ~ReadersWriters() {
    // All worker threads must be stopped and joined before destroying this.
    cout << "[rw] destroying synchronization objects" << endl;
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&stateChanged);
  }

  void reader(int id) {
    pthread_mutex_lock(&mutex);

    // Ticket assignment under the mutex defines the FIFO request order.
    const unsigned long long myTicket = nextTicket++;
    cout << "[reader " << id << "] got ticket " << myTicket << endl;

    // A reader may start when its ticket is up and no writer is active.
    // Advancing servingTicket lets the next consecutive reader enter too.
    while (myTicket != servingTicket || isWriting) {
      cout << "[reader " << id << "] waiting for ticket " << myTicket
           << "; serving=" << servingTicket
           << ", writer active=" << isWriting << endl;
      pthread_cond_wait(&stateChanged, &mutex);
    }

    ++readCount;
    ++servingTicket;
    cout << "[reader " << id << "] entering; next ticket=" << servingTicket
         << ", active readers=" << readCount << endl;

    // Broadcast because any waiter may wake; only the request whose ticket
    // is now serving can proceed. Consecutive readers can overlap.
    pthread_cond_broadcast(&stateChanged);
    pthread_mutex_unlock(&mutex);

    cout << "Reader " << id << " is reading." << endl;
    sleep(1);

    pthread_mutex_lock(&mutex);
    --readCount;
    cout << "[reader " << id << "] leaving; active readers=" << readCount
         << endl;
    if (readCount == 0) {
      // The next ticket may belong to a writer, which can proceed now.
      cout << "[reader " << id << "] last reader left; waking ticket waiters"
           << endl;
      pthread_cond_broadcast(&stateChanged);
    }
    pthread_mutex_unlock(&mutex);
  }

  void writer(int id) {
    pthread_mutex_lock(&mutex);

    // A writer gets its place in line just like a reader.
    const unsigned long long myTicket = nextTicket++;
    cout << "[writer " << id << "] got ticket " << myTicket << endl;

    // Keep servingTicket on the writer's ticket until it finishes. This
    // prevents any later reader or writer from passing the active writer.
    while (myTicket != servingTicket || isWriting || readCount > 0) {
      cout << "[writer " << id << "] waiting for ticket " << myTicket
           << "; serving=" << servingTicket
           << ", active readers=" << readCount
           << ", writer active=" << isWriting << endl;
      pthread_cond_wait(&stateChanged, &mutex);
    }

    isWriting = true;
    cout << "[writer " << id << "] entering with ticket " << myTicket
         << endl;
    pthread_mutex_unlock(&mutex);

    cout << "Writer " << id << " is writing." << endl;
    sleep(1);

    pthread_mutex_lock(&mutex);
    isWriting = false;
    ++servingTicket;
    cout << "[writer " << id << "] leaving; next ticket=" << servingTicket
         << "; waking waiters" << endl;
    // The next ticket may be a reader or another writer.
    pthread_cond_broadcast(&stateChanged);
    pthread_mutex_unlock(&mutex);
  }

private:
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t stateChanged = PTHREAD_COND_INITIALIZER;
  int readCount;
  bool isWriting;
  unsigned long long nextTicket;
  unsigned long long servingTicket;
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
