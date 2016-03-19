#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

QUEUE* init_queue() {

    QUEUE *q;
    q = (QUEUE*)malloc(sizeof(QUEUE));

    if(!q)
	return NULL;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

QNODE* create_qnode(char *oword, int suffix_idx) {
    QNODE *qnode;
    char *orig_word;

    qnode = (QNODE*)malloc(sizeof(QNODE));
    if(!qnode)
	return NULL;

    qnode->next = NULL;
    qnode->prev = NULL;
    qnode->suffix_idx = 0;
    /*create a new memory space for original word*/
    if(!(orig_word = (char*)calloc(WORD_SIZE, sizeof(char))))
	return NULL;
    /*copy the orginal word into a new memory */
    strncpy(qnode->oword, oword, WORD_SIZE);
    qnode->suffix_idx = suffix_idx;

    return qnode;
}

void enqueue(QUEUE *q, char *oword, int suffix_idx) {

    QNODE *qnode, *temp;

    if(!q || !oword || suffix_idx < 0)
	return;
    qnode = create_qnode(oword, suffix_idx);

    if(!qnode)
	return;

    if(!q->head){ //queue is empty
	q->head = qnode;
	q->tail = qnode;
    } else {
	temp = q->head;
	q->head = qnode;
	qnode->next = temp;
	temp->prev = qnode;
    }
}

void dequeue(QUEUE *q){

    QNODE *prev_node=NULL;

    if(!q || is_queue_empty(q))
	return;

    /*get to the previous node*/
    if(q->head != q->tail){

	prev_node = q->tail->prev;
	prev_node->next = q->tail->next;
	q->tail->prev = NULL;
	free(q->tail);
	q->tail = prev_node;
    } else {
	/*if there is only one node in the queue, free that node and set head/tail to NULL*/
	free(q->head);
	/*node = q->head;*/
	q->head = NULL;
	q->tail = NULL;
    }
}

int is_queue_empty(QUEUE *q) {
    return ((q && !q->head && !q->tail)?1:0); 
}

void print_queue(QUEUE *q) {
    QNODE *trav;

    if(!q || !q->head)
	return;
    trav = q->head;
    while(trav){
	printf("WORD = %s, SUFFIX = %s\n", trav->oword, trav->oword + trav->suffix_idx);
	trav = trav->next;
    }
}

void build_queue(QUEUE *q, TNODE *troot, char *oword) {

    int sidx = 0;
    if(!troot || !oword) {
	return;
    }

    /*len = strlen(oword);*/
    while(*(oword+sidx)!='\0') {

	if(*(oword+sidx) && troot->next[*(oword+sidx)-'a'] && troot->is_valid_word) {
	    /*we find a valid word as a prefix while going down the path of original word(oword) in a trie, 
	     * add the word and suffix into the queue */
	    enqueue(q, oword, sidx);
	}  
	troot = troot->next[*(oword+sidx)-'a'];	
	sidx++;
    }   
}

void process_queue(QUEUE *q, TNODE* troot, HASH *h) {

    int sidx = 0, oword_len = 0;
    char* oword = NULL;
    QNODE *qnode;
    TNODE *root = NULL;

    if(!q || !troot)
	return;
    root = troot;

    /* run the loop till the queue is empty*/
    while(!is_queue_empty(q)){

	qnode = q->tail;
	oword = qnode->oword;
	sidx = qnode->suffix_idx;
	oword_len = strlen(oword);

	printf("oword=%s, suffix=%s\n", oword, oword+sidx);
	troot = troot->next[*(oword+sidx)-'a'];
	while(*(oword+sidx)!='\0') {

	    /*if(troot->next[*(oword+sidx)-'a']) {*/
	    if(troot) {
		if(troot->is_valid_word) {
		    /*printf("troot->c %c  suffix %c\n", troot->c, *(oword+sidx)); */
		    /*we find a valid word as a prefix while going down the path of original word(oword) in a trie, 
		     * add the word and suffix into the queue */
		    if(sidx == oword_len-1){
			/*printf("hash insert\n"); */
			hash_insert(h, oword);
		    } else{
			/*printf("Insert into queue %s\n", oword+sidx+1);*/
			enqueue(q, oword, sidx+1);
		    }
		}
	    } else {
		/*if we do not find suffix we stop processing the suffix and dequeue*/
		printf("inside break\n");
		break;
	    }  
	    sidx++;
	    troot = troot->next[*(oword+sidx)-'a'];	
	}   
	troot = root;
	dequeue(q);
	}
    }

char *get_max_word(HASH *h) {

    return h?h->max_word:NULL;
}

char * get_sec_max_word(HASH *h) {

    return h?h->sec_max_word:NULL;
}


int hash_func(char * string) {

    int string_len=0;
    int total_val=0;

    if(!string)
       	return -1;

    string_len = strlen(string);
    while( *string != '\0') {
	total_val += *string;
	string++;
    }
    total_val += string_len;
    return (total_val % HASH_SIZE);
}

HASH* hash_init(){

    int i;
    HASH *h = NULL;

    h = malloc(sizeof(HASH));
    if(!h){
	return 0;
    }

    h->total_word_count = 0;
    h->max_word = NULL;
    h->sec_max_word = NULL;

    for(i=0; i < HASH_SIZE; i++) {
	h->bucket[i] = NULL;
    }
    return h;
}

HNODE* create_hash_node(char *string) {

    HNODE *hnode = NULL;
    if(!string)
	return NULL;

    hnode = (HNODE*)malloc(sizeof(HNODE));
    if(!hnode)
	return NULL;

    strncpy(hnode->oword, string, strlen(string)+1);
    hnode->next = NULL;

    return hnode;
}

int hash_destroy(HASH **hash) {

    HNODE *node=NULL, *tmpNode=NULL;
    HASH *hashLocal = NULL;
    int count=0;

    if (!hash || !*hash)
	return -1;

    hashLocal = *hash;
    for(count=0;count<HASH_SIZE;count++) {
	node = hashLocal->bucket[count];
	while(node) {
	    tmpNode = node->next;
	    free(node);
	    node = tmpNode;
	}

	free(hashLocal);
	*hash = NULL;

    }
    return 1;
}

    void hash_print(HASH *h) {

	HNODE *node = NULL;
	int count=0;

	if (!h) 
	    return;

	if (!h->total_word_count ) {
	    printf("HASH is empty\n");
	    return;
	}

	for(count=0; count < HASH_SIZE; count++) {
	    node = h->bucket[count];
	    if (node) {
		printf("[Bucket %d] :", count);
		while(node) {
		    printf("\t%s", node->oword);
		    node = node->next;
		}
		/*node = NULL;*/
		printf("\n");
	    }
	}	
    }

    int hash_search(HASH *h, char* string){

	int bucket_idx = 0; 
	HNODE *node = NULL;

	if (!string || !h)
	    return 0;

	bucket_idx = hash_func(string);
	if ((bucket_idx == -1) || !h->bucket[bucket_idx])
	    return 0;

	node = h->bucket[bucket_idx];
	while(node) {
	    if(!strcmp(node->oword, string)){
		/*string found*/
		return 1;
	    }
	    node = node->next;
	}
	return 0;
    }

    void hash_insert(HASH *h, char* string) {

	int bucket_idx = -1;
	HNODE *hnode=NULL;
	int max_word_len = 0, sec_max_word_len = 0;

	if (!string || !h)
	    return;

	/*if word is present in hash then, bail out*/
	if(hash_search(h, string))
	    return;

	bucket_idx = hash_func(string);

	/*node = h->bucket[bucket_idx];*/
	hnode = create_hash_node(string);

	if(!hnode)
	    return;

	hnode->next = h->bucket[bucket_idx];
	h->bucket[bucket_idx] = hnode;


	/*calculate the max and second max word*/
	if(!h->max_word && !h->sec_max_word) {
	    h->max_word = hnode->oword; 
	    h->sec_max_word = hnode->oword; 
	} else if(strlen(h->max_word) > strlen(h->max_word) && {

	}

	/*after inserting the word, update the total word count*/
	h->total_word_count++;
    }
