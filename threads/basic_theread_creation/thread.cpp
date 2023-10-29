#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int thread_num = *((int *)arg);
    printf("Hello from thread %d!\n", thread_num);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int thread1_arg = 1;
    int thread2_arg = 2;

    pthread_create(&thread1, NULL, thread_function, &thread1_arg);
    pthread_create(&thread2, NULL, thread_function, &thread2_arg);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
