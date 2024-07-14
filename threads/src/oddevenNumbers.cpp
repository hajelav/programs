/* Write a program that uses two threads to print odd and even numbers alternately.*/

#include <pthread.h>
#include <iostream>
#include <time.h>
#include <thread>
#include <functional>

using namespace std;
#define RANGE 100

// synchroniing the threads
pthread_mutex_t mutex;
// condition variables
pthread_cond_t cond1;
pthread_cond_t cond2;
int turn = 1;

void *thread_function_odd(void *tid)
{

    int id = *(static_cast<int *>(tid));

    for (int i = 1; i <= RANGE; i = i + 2)
    {
        pthread_mutex_lock(&mutex);
        while (turn != 1)
        {
            pthread_cond_wait(&cond1, &mutex);
        }
        cout << "Thread[" << id << "] : " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
        turn = 2;
        pthread_cond_signal(&cond2);
        pthread_mutex_unlock(&mutex);
    }
    cout << endl;
    return nullptr;
}

void *thread_function_even(void *tid)
{

    int id = *(static_cast<int *>(tid));

    for (int i = 2; i <= RANGE; i= i + 2)
    {
        pthread_mutex_lock(&mutex);
        while (turn != 2)
        {
            pthread_cond_wait(&cond2, &mutex);
        }
        cout << "Thread[" << id << "] : " << i << endl;
        turn = 1;
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&mutex);
    }
    cout << endl;
    return nullptr;
}

int main()
{

    pthread_t oddThread, evenThread;
    int odd = 1, even = 2;


    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond1, nullptr);
    pthread_cond_init(&cond2, nullptr);

    pthread_create(&oddThread, NULL, thread_function_odd, &odd);
    pthread_create(&evenThread, NULL, thread_function_even, &even);

    pthread_join(oddThread, nullptr);
    pthread_join(evenThread, nullptr);

    return 0;
}