#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <Queue.h>

using namespace std;

typedef struct task
{
    void (*cb)(void *);
    void *args;
} TASK;

class ThreadPool
{

public:
    ThreadPool(int size) : qSize(size) {
    currSize = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    }

    /* this is the function executed by threads in a thread pool, 
    any thread picks up any task from the taskQueue and call the function
    associated  with that task. These tasks are added by the clients. whenever a thread
    works on a task , it calls its cb functon */
    void workers() {


        while(1) {
            pthread_mutex_lock(&mutex);
            while(currSize == 0) {
                pthread_cond_wait(&empty, &mutex);
            }
            /* fetch the task from the front */
            TASK *task = taskQueue.front();
            /* call the cb requisted by the client in Add task function */
            task->cb(task->args);
            /* signal if there are any tasks to be added */
            pthread_cond_signal(&full);
            /* decrement the size of the queue */
            currSize--;

            pthread_mutex_unlock(&mutex);
        }

    }

    void addTask(TASK* task) {

        /* push the tasks into the queue in a thread safe manner*/
        pthread_mutex_lock(&mutex);
        while(currSize == qSize) {
            pthread_cond_wait(&full, &mutex);
        }   
        /* increment the size of the queue*/
        currSize++;
        taskQueue.push(task);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);

    };



private:
    int currSize;
    int qSize;
    queue<TASK*> taskQueue;
    // locking valriable
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
};


void simpleTask( int num) {
    cout << "Task : " << num << endl;
}
int main() {

ThreadPool *pool = new ThreadPool(8);


}