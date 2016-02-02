#include "../utils.h"

#define CIRCULAR_BUF_SIZE 5

typedef struct _cbuffer {
    int start; //pointer for dequeuing the buffer, we only delete using start pointer
    int end;   //pointer for queuing the buffer, we only add using end pointer
    int *cbuf; //array for circular buffer
    int size;  //size of circular buffer
    int curr_size; //current size of circular buffer
} CBUFFER;

CBUFFER* init_circular_buf() {

    CBUFFER *cb;
    cb = (CBUFFER*)malloc(sizeof(CBUFFER));

    if(!cb)
	return NULL;

    /*initialize start and end pointers*/
    cb->start = 0;
    cb->end = 0;
    cb->curr_size = 0;

    /*initialize the size */
    cb->size = CIRCULAR_BUF_SIZE;

    cb->cbuf = (int*)calloc(CIRCULAR_BUF_SIZE, sizeof(int));

    if(!cb->cbuf)
	return NULL;

    return cb;
}

/*add element to the queue*/
void enqueue(CBUFFER *cb, int elem) {

    if(!cb || !cb->cbuf || cb->size <=0)
	return;

    /*update the current size as long as it is less than the buffer size*/
    if(cb->curr_size < cb->size)
	cb->curr_size++;


    cb->end = cb->end%cb->size;
    cb->cbuf[cb->end] = elem;
    cb->end++;
}

/*delete element from the queue*/
void dequeue(CBUFFER *cb) {

    if(!cb || !cb->cbuf)
	return;

    /*if the current size becomes zero, then buffer is empty*/
    if(cb->curr_size == 0){
	printf("queue is empty\n");
	return;
    }

    /*
     *if the curent size becomes equal to the buffer size and start and end pointers are different,
     *that means the buffer is full and overwritten. so we just need delete the elements from the 
     *next position of that last added entry. We therefore point start to end(which is pointing to
     *the next of last added entry
     */
    if(cb->curr_size == cb->size && cb->start!=cb->end){
	cb->start = cb->end;
    }

    /*decrease the current size of buffer*/
    cb->curr_size--;

    cb->start = cb->start%cb->size;
    cb->cbuf[cb->start] = 0;
    cb->start++;
}

void print_circular_buffer(CBUFFER *cb) {

    int i;

    if(!cb || !cb->cbuf)
	return;

    for(i=0;i<cb->size;i++){
	printf("%d ", cb->cbuf[i]);
    }
}

int main() {

    char c;
    int choice;
    int num;
    CBUFFER *cb = NULL;

    /*initialize the buffer*/
    cb = init_circular_buf();

    do {

    printf("MENU OPTIONS\n");
    printf("1 -- enqueue circular buffer\n");
    printf("2 -- dequeue circular buffer\n");
    printf("3 -- print circular buffer\n");

    printf("Enter your choice\n");
    scanf("%d",&choice);

    switch(choice){

	case 1:
	    printf("enter number\n");
	    scanf("%d", &num);
	    enqueue(cb, num);
	    print_circular_buffer(cb);

	    break;

	case 2:
	    dequeue(cb);
	    print_circular_buffer(cb);
	    break;

	case 3:
	    print_circular_buffer(cb);
	    break;

	default:
	    printf("Invalid option\n");
	    break;
    }
    printf("\n\n");
    }while((c=getchar())!='q');
    return 0;
}

