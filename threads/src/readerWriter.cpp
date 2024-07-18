/* Implement the readers-writers problem using pthreads, mutexes, and condition variables.*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>

class ReadersWriters {
public:
    ReadersWriters() : readCount(0), isWriting(false) {
        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&readLock, nullptr);
        pthread_cond_init(&writeLock, nullptr);
    }

    ~ReadersWriters() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&readLock);
        pthread_cond_destroy(&writeLock);
    }

    void reader(int id) {
        pthread_mutex_lock(&mutex);
        while (isWriting) {
            pthread_cond_wait(&readLock, &mutex);
        }
        ++readCount;
        pthread_mutex_unlock(&mutex);

        std::cout << "Reader " << id << " is reading." << std::endl;
        sleep(1);

        pthread_mutex_lock(&mutex);
        --readCount;
        if (readCount == 0) {
            pthread_cond_signal(&writeLock);
        }
        pthread_mutex_unlock(&mutex);
    }

    void writer(int id) {
        pthread_mutex_lock(&mutex);
        while (isWriting || readCount > 0) {
            pthread_cond_wait(&writeLock, &mutex);
        }
        isWriting = true;
        pthread_mutex_unlock(&mutex);

        std::cout << "Writer " << id << " is writing." << std::endl;
        sleep(1);

        pthread_mutex_lock(&mutex);
        isWriting = false;
        pthread_cond_broadcast(&readLock);
        pthread_cond_signal(&writeLock);
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;
    pthread_cond_t readLock;
    pthread_cond_t writeLock;
    int readCount;
    bool isWriting;
};

void* readerTask(void* arg) {
    std::pair<ReadersWriters*, int>* data = static_cast<std::pair<ReadersWriters*, int>*>(arg);
    while (true) {
        data->first->reader(data->second);
        sleep(1);
    }
    return nullptr;
}

void* writerTask(void* arg) {
    std::pair<ReadersWriters*, int>* data = static_cast<std::pair<ReadersWriters*, int>*>(arg);
    while (true) {
        data->first->writer(data->second);
        sleep(2);
    }
    return nullptr;
}

int main() {
    ReadersWriters rw;
    pthread_t readers[5], writers[2];

    for (int i = 0; i < 5; ++i) {
        pthread_create(&readers[i], nullptr, readerTask, new std::pair<ReadersWriters*, int>(&rw, i));
    }

    for (int i = 0; i < 2; ++i) {
        pthread_create(&writers[i], nullptr, writerTask, new std::pair<ReadersWriters*, int>(&rw, i));
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(readers[i], nullptr);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_join(writers[i], nullptr);
    }

    return 0;
}
