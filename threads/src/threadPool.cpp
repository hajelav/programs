/*

In threadpool design, we create a threadpool of threads
and enqueue tasks in the threadpool. main thead enqueues
the tasks and waits for the tasks to complete. the worker threads
execute the tasks by looping on the task queue until it is empty.
if the task queue is empty and there are no more tasks to execute
the worker threads wait for new tasks to be enqueued.

*/

#include <pthread.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>

using namespace std;

class ThreadPool
{
public:
    static void *thread_function(void *arg)
    {
        /* each thread will  execute run() and run indefinitely*/
        ThreadPool *pool = static_cast<ThreadPool *>(arg);
        pool->run();
        return nullptr;
    }

    ThreadPool(size_t numThreads) : stop(false)
    {
        cout << "Starting  threadpool .." << endl;
        /* In the constructor start all the threads
         */
        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&cond, nullptr);
        for (size_t i = 0; i < numThreads; ++i)
        {
            pthread_t thread;
            /* each thread will execute thread_function() and run indefinitely
            pass the threadpool object as an argument*/
            pthread_create(&thread, nullptr, thread_function, this);
            workersThreads.push_back(thread);
        }
    }
    /* main thread enqueues the function and its arguments
    into the task queue of the threadPool*/
    void
    enqueue(void (*userFunc)(void *), void *arg)
    {
        /*  lock the task Q as many threads can
            consume the tasks from the task queue
            while main thread is pushing
        */
        pthread_mutex_lock(&mutex);
        tasks.push({userFunc, arg});
        /* once the task has been pushed, signal the pool thread
        that the task is ready to be consumed */
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    ~ThreadPool()
    {

        pthread_mutex_lock(&mutex);
        cout << "calling destructor" << endl;
        stop = true;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
        for (pthread_t &worker : workersThreads)
        {
            pthread_join(worker, nullptr);
        }
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }

    void stopThreadPool()
    {
        stop = true;
        cout << "Stopping threadpool .." << endl;
    }

private:
    /* function to be called by each thread in a threadpool*/

    void run()
    {
        /* all threads in a threadpool will be continously running*/
        while (true)
        {
            std::pair<void (*)(void *), void *> task;
            pthread_mutex_lock(&mutex);
            /* all the worker threads have to wait
            if there is no task in the task Q*/
            while (!stop && tasks.empty())
            {
                pthread_cond_wait(&cond, &mutex);
            }
            /* if the user has asked to stop the threadpool
            then we release the mutex*/
            if (stop && tasks.empty())
            {
                pthread_mutex_unlock(&mutex);
                return;
            }
            /* take out the task from front of Q*/
            task = tasks.front();
            /* pop the task*/
            tasks.pop();

            /* call the user defined function of the task
           task.first --> function name
           task.second --> function argument(void*)
           */
            task.first(task.second);
            pthread_mutex_unlock(&mutex);
        }
    }

    vector<pthread_t> workersThreads;
    /* task queue is queue of pair of user passed function
     and its argument
     */
    queue<std::pair<void (*)(void *), void *>> tasks;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool stop;
};

void printTask(void *arg)
{
    int id = *static_cast<int *>(arg);
    std::cout << "Task " << id << " is being processed" << std::endl;
    cout << endl;
}

int main()
{

    /* create a threadpool of 4 threads */
    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Task " << i << " is pushed into ThreadPool" << std::endl;
        cout << endl;
        pool.enqueue(printTask, new int(i));
    }

    sleep(2); // Allow some time for tasks to complete

    return 0;
}
