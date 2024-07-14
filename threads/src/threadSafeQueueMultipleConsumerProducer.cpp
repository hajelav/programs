#include <iostream>
#include <thread>
#include <queue>
#include <unistd.h>

using namespace std;

const int NUM_PRODUCERS = 5;
const int NUM_CONSUMERS = 5;
const int ITEMS_PER_PRODUCER = 3;

class TSQueue
{

public:
    TSQueue(int size)
    {
        m_size = size;
        m_currSize = 0;
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_cond_init(&m_empty, nullptr);
        pthread_cond_init(&m_full, nullptr);
    }

    ~TSQueue()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_empty);
        pthread_cond_destroy(&m_full);
    }

    void enqueue(int val)
    {

        pthread_mutex_lock(&m_mutex);
        while (m_currSize == m_size)
            pthread_cond_wait(&m_full, &m_mutex);
        m_queue.push(val);
        m_currSize++;
        pthread_cond_signal(&m_empty);
        pthread_mutex_unlock(&m_mutex);
    }

    int dequeue()
    {

        pthread_mutex_lock(&m_mutex);
        while (m_currSize == 0)
            pthread_cond_wait(&m_empty, &m_mutex);
        int val = m_queue.front();
        m_currSize--;
        m_queue.pop();
        pthread_cond_signal(&m_full);

        pthread_mutex_unlock(&m_mutex);
        return val;
    }

private:
    int m_currSize;
    int m_size;
    queue<int> m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_empty;
    pthread_cond_t m_full;
};

void* producer(void* arg) {

    TSQueue* tsq = static_cast<TSQueue*>(arg);
    //producer thread produces 10 items
    for(int i=0; i<ITEMS_PER_PRODUCER; i++) {
        tsq->enqueue(i);
         cout << "Thread Id=" << pthread_self() << " Produced: " << i << endl;
         sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {

    TSQueue* tsq = static_cast<TSQueue*>(arg);
    for(int i=0; i<ITEMS_PER_PRODUCER; i++) {
        int val = tsq->dequeue();
         cout << "Thread Id=" << pthread_self() << " Consumed: " << val << endl;
         sleep(2);
    }
    return nullptr;
}
int main() {

    TSQueue* tsq = new TSQueue(10);
   
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        if (pthread_create(&producers[i], nullptr, producer, tsq) != 0) {
            throw std::runtime_error("Failed to create producer thread");
        }
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        if (pthread_create(&consumers[i], nullptr, consumer, tsq) != 0) {
            throw std::runtime_error("Failed to create consumer thread");
        }
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], nullptr);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], nullptr);
    }



    return 0;
}