#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <queue>

using namespace std;

typedef struct task
{
    void (*func)(void *);
    void *args;
} TASK;

class ThreadPool
{

    ThreadPool(int size) : qSize(size) {
    currSize = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    }

    void AddTask(TASK* task) {
        
    }



private:
    int currSize;
    int qSize;
    queue<int> taskQueue;
    // locking valriable
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
};