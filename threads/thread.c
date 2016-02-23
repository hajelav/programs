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



//thread prototypes
void* thread0(void *data) {

    int i = 0;
    while(i<10) {
	sem_wait(&mutex[0]);
	printf("thread 0\n");
	sem_post(&mutex[1]);
	i++;
    }
    return NULL;

}

void* thread1(void *data) {
    int i = 0;
    while(i<10) {
	sem_wait(&mutex[1]);
	printf("thread 1\n");
	sem_post(&mutex[2]);
	i++;
    }
    return NULL;
}

void* thread2(void *data) {

    int i = 0;
    while(i<10) {
	sem_wait(&mutex[2]);
	printf("thread 2\n");
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


/*
 *thread to print even/odd numbers in the array.Note that the semaphores are just used for synchronization
 *of thread. We dont need semaphores for mutual exclusion as it is a lockless design(ie threads access differnt regions
 *of memory parallely)
 */
void* thread(void *data) {


    printf("Thread id : %ld\n", pthread_self());
    int tid;
    int i;
    TDATA *td;

    //deference the data passed from main thread
    td = (TDATA*)data;

    //get the tid
    tid = td->tid;

    for(i=0;i<N;i++) {

	if(i%2 == 0 && tid == 0){
	    sem_wait(&mutex1);
	    printf("%d (printed by thread %d)\n", td->arr[i], tid);
	    sem_post(&mutex2); //once thread 0 is done, it will increment mutex2 so that thread 1 can execute
	} else if(i%2 !=0 && tid == 1){
	    sem_wait(&mutex2); //thread 1 will always execute after thread 0, if thread one tries to print, it will be put to sleep
	    printf("%d (printed by thread %d)\n", td->arr[i], tid);
	    sem_post(&mutex1); //once thread 1 is done it will increment mutex1 so that thread 0 can execute
	}
    }
    return NULL;
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

typedef struct data {
    int *num; //number to print
    int *no_of_threads;
    int tid;
    sem_t *mutex_t;
} DATA;

void* thread_print(void *data) {

    int tid, no_of_threads, num;
    int i;
    DATA *tdata;
    printf("Thread id : %ld\n", pthread_self());

    //deference the data passed from main thread
    tdata = (DATA*)data;

    //get the tid
    tid = tdata->tid;

    //get no of threads
    no_of_threads = *(tdata->no_of_threads);
    printf("No of threads : %d\n", no_of_threads);

    //get the number
    num = *(tdata->num);
    printf("No : %d\n", num);

    for(i=0;i<num;i++) {

	if(i%no_of_threads ==  tid) {
	    sem_wait(&tdata->mutex_t[tid%no_of_threads]);
	    printf("%d -- printed by Thread %d [thread id:%ld]\n", i, tid, pthread_self());
	    sem_post(&tdata->mutex_t[(tid+1)%no_of_threads]);
	}
    }
    return NULL;
}

void print_numbers(int num, int nThreads){

    int i;
    DATA * data;
    int *number;
    int *no_of_threads;
    sem_t *mutex_t;

    //array to store n thread ids
    pthread_t tid[nThreads];

    //array of mutexes
    /*sem_t mutex[nThreads];*/

    /*initiaize the thread data equal to number of threads(n)*/
    data = (DATA*)malloc(sizeof(DATA)*nThreads);
    number = (int*)malloc(sizeof(int));
    no_of_threads = (int*)malloc(sizeof(int));
    mutex_t = (sem_t*)malloc(sizeof(sem_t)*nThreads);

    if(!data || !number || !no_of_threads || !mutex_t)
	return;

    *number = num;
    *no_of_threads = nThreads;

    //initialize the semaphores/mutexes
    for(i=0;i<nThreads;i++) {
	//initize the first mutes as 1 for synchronisation of threads
	if(i==0)
	    sem_init(&mutex_t[i], 0, 1); 
	else 
	    sem_init(&mutex_t[i], 0, 0); 
    }

    for(i=0;i<nThreads;i++){
	data[i].num = number;
	data[i].no_of_threads = no_of_threads;
	data[i].mutex_t = mutex_t;
	data[i].tid = i;
	pthread_create(&tid[i], NULL, thread_print, &data[i]);
    }

    for(i=0;i<nThreads;i++) {
	pthread_join(tid[i], NULL);
    }

    for(i=0;i<nThreads;i++) {
	sem_destroy(&mutex_t[i]); 
    }
}

int main(){

    char c;
    int choice;
    int m, n;

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- Using threads for synchronisation\n");
	printf("2 -- Thread printing even and odd numbers\n");
	printf("3 -- Printing m numbers(1 to m) alternatively using n threads\n");

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

	    case 3:
		printf("Enter m\n");
		scanf("%d", &m);
		printf("Enter no of threads\n");
		scanf("%d", &n);
		print_numbers(m, n);
		break;

	    default:
		break;
	}
	printf("\n\n");
    } while((c=getchar())!='q'); 
    return 0;
}
