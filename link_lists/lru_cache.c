#include <stdio.h>
#include <stdlib.h>

#define QUEUE_LEN 4 
#define HASH_SIZE 10
/*
 *date structures for LRU cache : doubly link list with Queue implementation.
 *Node at the front are always recent , whereas nodes at the end are the least used.
 */
typedef struct QNODE {
    int page_no;
    struct QNODE *prev;
    struct QNODE *next;
} QNODE;

/*
 * hash is used to access the actual nodes in the cache quickly at O(1) time.
 */
typedef struct HASH {
    int capacity; // no of pages that can be requested. for eg 0-9 in this implementation
    QNODE **arr;  //ptr to array of pointers to QNODEs 
} HASH;

typedef struct QUEUE {
    int csize; 	   // cache size
    int curcsize;  //current cache size;
    QNODE *head;   // head of the queue (to insert more recent used entry)
    QNODE *tail;   // tail to queue(to evict the least recently used page)
} QUEUE;

HASH* create_hash(int capacity) {

    int i;
    HASH *hash;

    if(capacity <=0)
	return NULL;

    /*allocate space for hash*/
    hash = (HASH*)malloc(sizeof(HASH));
    if(!hash)
	return NULL;
    hash->capacity = capacity;

    /*allocate space of the array of pointers to QNODEs*/
    hash->arr = (QNODE**)malloc(sizeof(QNODE)*capacity);

    /*initialize thr array*/
    for(i=0;i<capacity;i++){
	hash->arr[i] = NULL;
    }

    return hash;
}

QUEUE* create_queue( int cacheSize) {

    QUEUE *q;
    q = (QUEUE*)malloc(sizeof(QUEUE));
    
    if(!q)
	return NULL;
    q->csize = cacheSize;
    //initialize current cache size to 0
    q->curcsize = 0;
    
    q->head = NULL;
    q->tail = NULL;

    return q;
}

QNODE* create_qnode(int pageno) {
    QNODE *qnode;
    
	qnode = (QNODE*)malloc(sizeof(QNODE));
	if(!qnode)
	    return NULL;
    qnode->page_no =  pageno;
    qnode->next = NULL;
    qnode->prev = NULL;

    return qnode;
}

int lookup(HASH* hash, int pno) {
    return (hash->arr[pno]?1:0);
}

/*add page to the cache*/
void enqueue(HASH* hash, QUEUE *q, int pno) {

    QNODE *qnode, *temp;

     qnode = create_qnode(pno);

     if(!qnode)
	 return;
     
    if(!q->head){ //cache is empty
	q->head = qnode;
	q->tail = qnode;
    } else {
	temp = q->head;
	q->head = qnode;
	qnode->next = temp;
	temp->prev = qnode;
    }

    //add the page to the hash array
    hash->arr[pno] = qnode;
    //increment the current cache size
    if(q->curcsize < q->csize)
	q->curcsize +=1;
}

void dequeue(HASH *hash, QUEUE *q, int pno){

    QNODE *temp;

    if(!hash || !q)
	return;

    //if the page to be evicted(deleted) is head or tail we need to  update the QUEUE data structure 
    if(hash->arr[pno] == q->head){

	temp = hash->arr[pno];
        q->head = temp->next;
	free(temp);

    } else if(hash->arr[pno] == q->tail){
	temp = q->tail->prev;
	if(temp)
	    temp->next = NULL;
	free(q->tail);
	q->tail = temp;
    } else { //page evicted lies in between head and tail
	temp = hash->arr[pno];
	temp->prev = temp->next;
	temp->next->prev = temp->prev;
	free(temp);
    }
    //remove the page from hash array
    hash->arr[pno] = NULL;
    if(q->curcsize>0)
	q->curcsize -= 1;
}

void refer_page( HASH *hash, QUEUE *q, int page_no) {

    //first look up, if the page exist in the cache
    if(lookup(hash, page_no)){
	//page found
	
	dequeue(hash, q, page_no); //remove the found page first
	//insert it at the head
	enqueue(hash, q, page_no);

    } else { //page not found

	if(q->curcsize < q->csize)  { // cache has space to insert a page
	    enqueue(hash, q, page_no);
	} else {
	    //page is not found, but cache is already full. we need to first evict 
	    //least recently used page(pointed by tail) and the new node
	    dequeue(hash, q, q->tail->page_no); //remove the LRU ( ie at the tail)
	    enqueue(hash, q, page_no);
	}
    }
}

void print_cache(QUEUE *q){

    if(!q)
	return;
    QNODE *trav;
    trav = q->head;
    while(trav){
	printf("%d ", trav->page_no);
	trav = trav->next;
    }
    printf("\n");
}

int main(){

    int i,n,pno;
    QUEUE *q;
    HASH  *hash;


    q = create_queue(QUEUE_LEN);
    hash = create_hash(HASH_SIZE);

    printf("Enter the number of pages\n");
    scanf("%d",&n);

    printf("Enter page numbers\n");
    for(i=0;i<n;i++){
	scanf("%d", &pno);
	refer_page(hash, q, pno);
    }
    print_cache(q);
    return 0;
}
