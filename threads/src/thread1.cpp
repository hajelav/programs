/*
Implementing producer/consumer problem using condition variables
without using a buffer class
*/
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <queue>
#include <thread>
#include <functional>
#include <pthread.h>

using namespace std;

/* decelarations  of global shared variables */

#define NUM_PRODUCER_THREADS 5
#define NUM_CONSUMER_THREADS 5
#define QUEUE_SIZE 10

int m_bufSize;
queue<int> m_buf;
int m_currSize;

// thread synchroniztion mechanism
pthread_mutex_t mutex;
// condition variables
pthread_cond_t producer;
pthread_cond_t consumer;

// add element into the buffer
void enqueue(int num)
{

    pthread_mutex_lock(&mutex);
    // block the producer thread when the Q is full
    while (m_currSize == m_bufSize - 1)
        pthread_cond_wait(&producer, &mutex);
    cout << "Pushing : " << num << endl;
    m_buf.push(num);
    m_currSize++;

    // send signal to consumer that element is ready to be consumed
    pthread_cond_signal(&consumer);
    pthread_mutex_unlock(&mutex);
}

int dequeue()
{
    int front;
    pthread_mutex_lock(&mutex);
    // block the consumer, when the Q is empty
    while (m_currSize < 0)
        pthread_cond_wait(&consumer, &mutex);
    front = m_buf.front();
    cout << "Popping : " << front << endl;
    m_buf.pop();
    m_currSize--;
    pthread_cond_signal(&producer);
    pthread_mutex_unlock(&mutex);
    return front;
}

int main()
{

    // create a vector or producers

    vector<thread> producers;
    vector<thread> consumers;

    m_currSize = -1;
    m_bufSize = QUEUE_SIZE;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&producer, NULL);
    pthread_cond_init(&consumer, NULL);

    // create producer threads
    for (int i = 0; i < NUM_PRODUCER_THREADS; i++)
    {
        // pthread_create(&producers[i], NULL, producer, (void*)&i);
        int num = rand() % m_bufSize;
        producers.push_back(thread(enqueue, num));
    }

    // create 5 consumer threads
    for (int i = 0; i < NUM_CONSUMER_THREADS; i++)
    {
        consumers.push_back(thread(dequeue));
    }

    for (int i = 0; i < NUM_PRODUCER_THREADS; i++)
    {
        producers[i].join();
    }
    for (int i = 0; i < NUM_CONSUMER_THREADS; i++)
    {

        consumers[i].join();
    }

    return 0;
}
