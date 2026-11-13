# Pthreads interview practice

Work through these examples in order. The first six cover the core pthread
interview patterns; the timer is an optional stretch exercise.

1. `01_shared_counter.cpp` — create/join threads, protect shared state with a mutex.
2. `02_thread_arguments.cpp` — pass per-thread data and manage its lifetime.
3. `03_alternating_threads.cpp` — coordinate turns with a condition variable.
4. `04_condvar_signal_broadcast.c` — compare waking one waiter with waking all.
5. `05_condvar_timeout.c` — wait on a condition variable with a deadline.
6. `06_bounded_producer_consumer.cpp` — use a bounded queue and condition variables.
7. `07_thread_pool.cpp` — dispatch queued work to worker threads; practice shutdown.
8. `08_timer_priority_queue.cpp` — optional timer/cancellation exercise.

Compile C++ examples with:

```sh
g++ -std=c++11 -g -Wall -Wextra -pthread -o thread file.cpp
```

Compile C examples with:

```sh
gcc -std=c11 -g -Wall -Wextra -pthread -o thread file.c
```

`build/` contains the pre-existing compiled executables; rebuild from the
source files when needed.
