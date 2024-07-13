/*
Implementing producer/consumer problem using condition variables

*/
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <queue>
#include <thread>
#include <functional>

using namespace std;

#define NUM_PRODUCER_THREADS 5
#define NUM_CONSUMER_THREADS 5

class ProducerConsumer
{

public:
    ProducerConsumer(int bufSize) : m_bufSize(bufSize)
    {

        m_currSize = -1;
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&producer, NULL);
        pthread_cond_init(&consumer, NULL);
    }
    ~ProducerConsumer() {
         pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&producer);
        pthread_cond_destroy(&consumer);
    }

    void start()
    {
        // Create producer threads
        for (int i = 0; i < NUM_PRODUCER_THREADS; ++i)
        {
            int num = rand() % m_bufSize;
            producer_threads.push_back(thread(&ProducerConsumer::enqueue, this, num, i));
        }

        // Create consumer threads
        for (int i = 0; i < NUM_CONSUMER_THREADS; ++i)
        {
            consumer_threads.push_back(thread(&ProducerConsumer::dequeue, this, i));
        }

        for (int i = 0; i < NUM_PRODUCER_THREADS; i++)
        {
            producer_threads[i].join();
        }
        for (int i = 0; i < NUM_CONSUMER_THREADS; i++)
        {

            consumer_threads[i].join();
        }

        // Signal consumers to stop
        //{
        //    std::lock_guard<std::mutex> lock(mtx);
        //    stop_production = true;
        //    cond_empty.notify_all();
        //}
    }

    // add element into the buffer
    void enqueue(int num, int tid)
    {

        pthread_mutex_lock(&mutex);
        // block the producer thread when the Q is full
        while (m_currSize == m_bufSize - 1)
            pthread_cond_wait(&producer, &mutex);
        cout << "Thread " << tid << " pushing " << num << endl;
        m_buf.push(num);
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
        m_currSize++;

        // send signal to consumer that element is ready to be consumed
        pthread_cond_signal(&consumer);
        pthread_mutex_unlock(&mutex);
    }

    int dequeue(int tid)
    {
        while (true)
        {
            int front;
            pthread_mutex_lock(&mutex);
            // block the consumer, when the Q is empty
            while (m_currSize < 0)
                pthread_cond_wait(&consumer, &mutex);
            front = m_buf.front();
            //this_thread::sleep_for(chrono::milliseconds(rand() % 100));
            cout << "Thread " << tid << " consumed " << front << endl;
            m_buf.pop();
            m_currSize--;
            pthread_cond_signal(&producer);
            pthread_mutex_unlock(&mutex);
            return front;
        }
    }

private:
    int m_bufSize;
    queue<int> m_buf;
    int m_currSize;
    // thread synchroniztion mechanism
    pthread_mutex_t mutex;
    // condition variables
    pthread_cond_t producer;
    pthread_cond_t consumer;
    vector<thread> producer_threads;
    vector<thread> consumer_threads;
    bool stop;
};

int main()
{

    ProducerConsumer pc(10);
    pc.start();
    return 0;
}
