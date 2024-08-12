#include <iostream>
#include <thread>
#include <queue>
#include <unistd.h>

using namespace std;

class TSQueue
{

public:
    TSQueue(int size)
    {
        m_size = size;
        m_currSize = 0;
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_cond_init(&consumerCond, nullptr);
        pthread_cond_init(&producerCond, nullptr);
    }

    ~TSQueue()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&consumerCond);
        pthread_cond_destroy(&producerCond);
    }

    void enqueue(int val)
    {

        pthread_mutex_lock(&m_mutex);
        while (m_currSize == m_size)
            pthread_cond_wait(&producerCond, &m_mutex);
        m_queue.push(val);
        m_currSize++;
        pthread_cond_signal(&consumerCond);
        pthread_mutex_unlock(&m_mutex);
    }

    int dequeue()
    {

        pthread_mutex_lock(&m_mutex);
        while (m_currSize == 0)
            pthread_cond_wait(&consumerCond, &m_mutex);
        int val = m_queue.front();
        m_currSize--;
        m_queue.pop();
        pthread_cond_signal(&producerCond);

        pthread_mutex_unlock(&m_mutex);
        return val;
    }

private:
    int m_currSize;
    int m_size;
    queue<int> m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t consumerCond;
    pthread_cond_t producerCond;
};

void *producer(void *arg)
{

    TSQueue *tsq = static_cast<TSQueue *>(arg);
    // producer thread produces 10 items
    for (int i = 0; i < 10; i++)
    {
        tsq->enqueue(i);
        cout << "Produced: " << i << endl;
        sleep(1);
    }
    return nullptr;
}

void *consumer(void *arg)
{

    TSQueue *tsq = static_cast<TSQueue *>(arg);
    for (int i = 0; i < 10; i++)
    {
        int val = tsq->dequeue();
        cout << "Consumed: " << val << endl;
        sleep(2);
    }
    return nullptr;
}
int main()
{

    /* create a queue of size 10*/
    TSQueue *tsq = new TSQueue(10);
    pthread_t pThreadId, cThreadId;

    pthread_create(&pThreadId, nullptr, producer, tsq);
    pthread_create(&cThreadId, nullptr, consumer, tsq);
    pthread_join(pThreadId, nullptr);
    pthread_join(cThreadId, nullptr);

    return 0;
}