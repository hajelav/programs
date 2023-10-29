#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>

using namespace std;

void *thread_function(void *arg) {

    //int thread_num = *((int *)arg);
    int thread_num = 0;
    printf("Hello from thread %d!\n", thread_num);
    pthread_exit(NULL);
}

int main() {

    //create a vector or producers
    int num_threads = 5;
    vector<pthread_t> producers(num_threads);
    vector<pthread_t> consumers(num_threads);

    //create 5 producers threads
    for(int i=0; i<num_threads; i++) {
        pthread_create(&producers[i], NULL, thread_function, NULL);
    }
    //create 5 consumer threads
    for(int i=0; i<num_threads; i++) {
        pthread_create(&consumers[i], NULL, thread_function, NULL);
    }

   for(int i=0; i<5; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
   }
    
    return 0;
}
