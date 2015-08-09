#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>  /*  Semaphore */ 
#include <unistd.h>


#define THREADS 3
#define N 10 //no of elements in array

//data to be passed to the thread;
typedef struct td{
    int *arr;
    int tid;
} TDATA;

//create an array of semaphore varaibles
sem_t mutex[THREADS];
sem_t mutex1;
sem_t mutex2;
/*sem_t mutex3;*/

void init_mutex() {
   sem_init(&mutex[0], 0, 1); 
   sem_init(&mutex[1], 0, 0); 
   sem_init(&mutex[2], 0, 0); 
}

//thread to print even/odd numbers in the array.Note that the semaphores are just used for synchronization
//of thread. We dont need semaphores for mutual exclusion as it is a lockless design(ie threads access differnt regions
//of memory parallely)
void* thread(void *data) {


    printf("Thead id : %ld\n", pthread_self());
    int tid;
    int i;
    TDATA *td;
    //deference the data passed from main thread
    td = (TDATA*)data;
    //get the tid
    tid = td->tid;

    //first thread prints even numbers
    if(tid == 0){
	for(i=0;i<N;i+=2) {
	    sem_wait(&mutex1);
	    printf("%d (printed by thread %d)\n", td->arr[i], tid);
	    sem_post(&mutex2); //once thread 0 is done, it will increment mutex2 so that thread 1 can execute

	}
    }
    //second thread prints odd numbers
    if(tid == 1){
	for(i=1;i<N;i+=2){
	    sem_wait(&mutex2); //thread 1 will always execute after thread 0, if thread one tries to print, it will be put to sleep
	    printf("%d (printed by thread %d)\n", td->arr[i], tid);
	    sem_post(&mutex1); //once thread 1 is done it will increment mutex1 so that thread 0 can execute
	}
    }

    return NULL;
}

//thread prototypes
void* thread0(void *data) {

    int i = 0;
    while(i<10) {
	sem_wait(&mutex[0]);
	printf("0");
	sem_post(&mutex[1]);
	i++;
    }
    return NULL;

}

void* thread1(void *data) {
    int i = 0;
    while(i<10) {
	sem_wait(&mutex[1]);
	printf("1");
	sem_post(&mutex[2]);
	i++;
    }
    return NULL;
}

void* thread2(void *data) {

    int i = 0;
    while(i<10) {
	sem_wait(&mutex[2]);
	printf("2");
	sem_post(&mutex[0]);
	i++;
    }
    return NULL;
}


/*
 *this function synchronises the order of threads so that the following order is maintained
 *thread0->first
 *thread1->second
 *thread2->third
 */

void sync_threads() {

    //init the mutex variables
    init_mutex();

    //create thread ids
    pthread_t tid[THREADS];

    pthread_create(&tid[0], NULL, thread0, NULL);
    pthread_create(&tid[1], NULL, thread1, NULL);
    pthread_create(&tid[2], NULL, thread2, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    sem_destroy(&mutex[0]);
    sem_destroy(&mutex[1]);
    sem_destroy(&mutex[2]);
}


void even_odd_print() {

    int i;
    TDATA *td;
    int *arr;
    //initialize semaphores for synchonizing thread 0 and 1
    sem_init(&mutex1, 0, 1); 
    sem_init(&mutex2, 0, 0); 

    //create an array of td equal to number of threads(2)
    td = (TDATA*)malloc(sizeof(TDATA)*2);
    //shared array, which is manipulated by threads
    arr = (int*)malloc(sizeof(int)*N);

    //init the array
    for(i=0;i<N;i++){
	arr[i] = i;
    }
    //create two threads, which wil print even and odd numbers
    pthread_t tid[2];

    for(i=0;i<2;i++){
	//create an int variable from heap to pass to the thread, since thread function has an argument type of void *
	td[i].arr = arr;
	td[i].tid = i;
	pthread_create(&tid[i], NULL, thread, &td[i]);
    }

    for(i=0;i<2;i++){
	pthread_join(tid[i], NULL);
    }

    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
}

int main(){


    char c;
    int choice;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Using threads for synchronisation\n");
	printf("2 -- Thread printing even and odd numbers\n");

	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		sync_threads();
		break;

	    case 2:
		even_odd_print();
		break;

	    default:
		break;

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
