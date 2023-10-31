/*
Implementing producer/consumer problem using condition variables

*/
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <queue>

using namespace std;

#define NUM_PRODUCER_THREADS 5
#define NUM_CONSUMER_THREADS 5


class Buffer {

    public:
        Buffer(int bufSize) : m_bufSize(bufSize) {
           
            m_currSize = -1;
            pthread_mutex_init(&mutex, NULL);
            pthread_cond_init(&producer, NULL);
            pthread_cond_init(&consumer, NULL);
        }
        ~Buffer() {}

    //add element into the buffer 
    void enqueue(int num) {

        pthread_mutex_lock(&mutex);
        //block the producer thread when the Q is full
        while (m_currSize == m_bufSize-1) 
            pthread_cond_wait(&producer, &mutex);
        m_buf.push(num);
        m_currSize++;

        //send signal to consumer that element is ready to be consumed
        pthread_cond_signal(&consumer);
        pthread_mutex_unlock(&mutex);
        
    }

    int dequeue() {
        int front;
         pthread_mutex_lock(&mutex);
          //block the consumer, when the Q is empty
        while(m_currSize < 0)
            pthread_cond_wait(&consumer, &mutex);
        front = m_buf.front();
        m_buf.pop();
        m_currSize--;
        pthread_cond_signal(&producer);
        pthread_mutex_unlock(&mutex);
        return front;
    }    

        
    private:
        int m_bufSize;
        queue<int> m_buf;
        int m_currSize;
        //thread synchroniztion mechanism
        pthread_mutex_t mutex;
        //condition variables
        pthread_cond_t producer;
        pthread_cond_t consumer;

    
};

void* producer(void*) {


}

void* consumer(void*) {

}


int main() {

    //create a vector or producers
    
    vector<pthread_t> producers(NUM_PRODUCER_THREADS);
    vector<pthread_t> consumers(NUM_CONSUMER_THREADS);
   

    //create a shared buffer 
    Buffer *buf = new Buffer(10);
    //create 5 producers/consumer threads
    for(int i=0; i<NUM_PRODUCER_THREADS; i++) {
        pthread_create(&producers[i], NULL, buf->enqueue(i), NULL);
       
    }
    for(int i=0; i<NUM_PRODUCER_THREADS; i++) {
        pthread_create(&producers[i], NULL, producer, (void*)account);
        pthread_create(&consumers[i], NULL, consumer, (void*)account);
    }
    

   for(int i=0; i<num_threads; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
   }
    pthread_mutex_destroy(&mutex);
    return 0;
}
