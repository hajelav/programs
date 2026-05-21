#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <vector>
#include <chrono>

class TaskScheduler
{
private:
    std::queue<std::function<void()>> queue_;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    static constexpr size_t MAX_SIZE = 1000;
    static constexpr auto WAIT_TIMEOUT = std::chrono::milliseconds(500);
    bool is_shutdown_ = false; // Flag to safely stop worker threads

public:
    void submitTask(std::function<void()> task)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        // Wait as long as the queue is full AND we aren't trying to shut down.
        // Timed waiting avoids indefinitely blocking submitters.
        while (queue_.size() >= MAX_SIZE && !is_shutdown_)
        {
            if (not_full_.wait_for(lock, WAIT_TIMEOUT) == std::cv_status::timeout)
            {
                std::cerr << "[Scheduler] submitTask timed out waiting for free queue space.\n";
                return;
            }
        }

        if (is_shutdown_)
        {
            return; // Reject new tasks if the system is closing
        }

        queue_.push(std::move(task));
        not_empty_.notify_one();
    }

    void workerLoop()
    {
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);

                // Wait as long as the queue is empty AND we aren't shutting down.
                // Timed waiting prevents workers from sleeping forever when idle.
                while (queue_.empty() && !is_shutdown_)
                {
                    if (not_empty_.wait_for(lock, WAIT_TIMEOUT) == std::cv_status::timeout)
                    {
                        std::cerr << "[Worker] wait timed out; continuing to poll for tasks/shutdown.\n";
                    }
                }

                // If shutdown was requested and all remaining tasks are processed, exit loop
                if (is_shutdown_ && queue_.empty())
                {
                    break;
                }

                task = std::move(queue_.front());
                queue_.pop();
                not_full_.notify_one();
            }

            // Execute the task outside the mutex lock to maximize concurrency
            if (task)
            {
                task();
            }
        }
    }

    void shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            is_shutdown_ = true;
        }
        // Wake up all threads waiting on either condition variable
        not_empty_.notify_all();
        not_full_.notify_all();
    }
};

// ==========================================
// Client Side Simulation Code
// ==========================================

// Free-standing client functions to pass to the scheduler instead of lambdas
void processTaskOne()
{
    std::cout << "[Worker] Executing Task One on thread " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void processTaskTwo()
{
    std::cout << "[Worker] Executing Task Two on thread " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main()
{
    TaskScheduler scheduler;

    // 1. Spin up a pool of 3 worker threads running our scheduler loop
    std::vector<std::thread> workerThreads;
    for (int i = 0; i < 3; ++i)
    {
        workerThreads.emplace_back(&TaskScheduler::workerLoop, &scheduler);
    }

    // 2. Submit tasks to the scheduler using traditional function pointers
    std::cout << "[Client] Submitting tasks to the scheduler...\n";
    scheduler.submitTask(processTaskOne);
    scheduler.submitTask(processTaskTwo);
    scheduler.submitTask(processTaskOne);
    scheduler.submitTask(processTaskTwo);

    // Give the worker threads a brief moment to process the work
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 3. Gracefully shutdown the scheduler
    std::cout << "[Client] Initiating graceful shutdown...\n";
    scheduler.shutdown();

    // 4. Join the threads back to the main thread for a clean exit
    for (auto &t : workerThreads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    std::cout << "[Client] All worker threads finished. System closed safely.\n";
    return 0;
}