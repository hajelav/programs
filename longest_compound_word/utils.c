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
	qnode->string_len = strlen(oword);
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
	QNODE *node = NULL;
    if(!q || is_queue_empty(q))
	return;

    /*get to the previous node*/
    if(q->head != q->tail){

		prev_node = q->tail->prev;
		prev_node->next = q->tail->next;
		q->tail->prev = NULL;
		node = q->tail;
		free(q->tail);
		q->tail = prev_node;
    } else {
	/*if there is only one node in the queue, free that node and set head/tail to NULL*/
		free(q->head);
		node = q->head;
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

    int sidx = 0, len=0;
    if(!troot || !oword) {
	return;
    }

    len = strlen(oword);
    while((troot) && (*(oword+sidx)!='\0')) {
	troot = troot->next[*(oword+sidx)-'a'];	
	sidx++;
	/*if(*(oword+sidx) && troot->next[*(oword+sidx)-'a'] && troot->next[*(oword+sidx)-'a']->is_valid_word) {*/
	//if(*(oword+sidx) && troot->next[*(oword+sidx)-'a'] && troot->is_valid_word) {
	if (troot->is_valid_word) {
	    /*we find a valid word as a prefix while going down the path of original word(oword) in a trie, 
	     * add the word and suffix into the queue */
	    /*if(sidx != len) {*/
	    enqueue(q, oword, sidx);
	    /*}*/
	}  
    }   
 }

void process_queue(QUEUE *q, TNODE* troot, HASH *hash) {
	int sidx = 0, len=0;
	TNODE *root = NULL;
	QNODE *node= NULL;
	char* oword = NULL;

    if(!q || !troot )
	return;

	/*node = dequeue(q);*/
    /*run the loop till the queue is empty*/
    while(node){
		root = troot;
		oword = node->oword;
		sidx = node->suffix_idx;
		
		while( (root) && (*(oword+sidx)!='\0')) {
			root = root->next[*(oword+sidx)-'a'];
			sidx++;
			if (root && (root->is_valid_word) ) {
				if( sidx == len ){
					hash_insert( hash, oword);
				} else {
					enqueue(q, oword, sidx);
    			}
			}	
		}
		free(node);
		/*node = dequeue(q);		*/
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
       	return 0;

    string_len = strlen(string);
    while( *string != '\0') {
	total_val += *string;
	string++;
    }
    total_val += string_len;
    return (total_val % HASH_SIZE);
}

int hash_init(HASH *hash){

    int i;
    HASH *h = NULL;

    h = malloc(sizeof(HASH));

    if(!hash ){
	return 0;
    }

    h->total_word_count;
    h->max_word = NULL;
    h->sec_max_word = NULL;

    for(i=0; i < HASH_SIZE; i++) {
	h->bucket[i] = NULL;
    }
    return 1;
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
		node = NULL;
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
	if (!bucket_idx || !h->bucket[bucket_idx])
	    return 0;

	node = h->bucket[bucket_idx];
	while(node) {
	    if(!strcmp(node->oword, string)){
		//string found
		return bucket_idx;
	    }
	    node = node->next;
	}
	return 0;
    }

int hash_insert(HASH *hash, char* string) {
    int bucket_idx = -1;
    HNODE *node=NULL,*tmpNode=NULL;

    if (!string || !hash || !hash->is_init)
	return -1;

    bucket_idx = hash_search(hash, string);
    if (bucket_idx != -1) {
	//string found
	return 1;
    }
    bucket_idx = calculate_hash(string);
    node = hash->bucket[bucket_idx];
    tmpNode = malloc(sizeof(HNODE));
    if(!tmpNode) {
	return -1;
    }
    tmpNode->next = NULL;
    strncpy(tmpNode->oword, string, strlen(string));
    tmpNode->length = strlen(string);
    tmpNode->next = hash->bucket[bucket_idx];
    hash->bucket[bucket_idx] = tmpNode;
    hash->string_count++;
    return 1;
}
