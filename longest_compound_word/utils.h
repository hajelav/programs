#ifndef	_UTILS_H_
#define	_UTILS_H_
#include "trie.h"

#define WORD_SIZE 128
#define HASH_SIZE 23

typedef struct QNODE {
    char oword[WORD_SIZE]; //original word
    int suffix_idx; //suffix index (the actual suffix will be oword+suffix_idx)
    struct QNODE *prev;
    struct QNODE *next;
} QNODE;

typedef struct QUEUE {
    int qsize;     // size
    QNODE *head;   // head of the queue (to insert)
    QNODE *tail;   // tail to queue(to delete)
} QUEUE;

typedef struct HNODE {
    char oword[WORD_SIZE]; //original word
    struct HNODE *next;
} HNODE;

typedef struct HASH {
    HNODE *bucket[HASH_SIZE];
    int total_word_count;
    char *max_word;
    char *sec_max_word;
} HASH;

//queue API
QUEUE* init_queue();
QNODE* create_qnode(char *oword, int suffix_idx);
void enqueue(QUEUE* q, char *oword, int suffix_idx);
void dequeue(QUEUE* q); 
void build_queue(QUEUE *q, TNODE* troot, char *oword);
void process_queue(QUEUE *q, TNODE* troot, HASH* hash);
int is_queue_empty(QUEUE *q);
void print_queue(QUEUE *q);
void queue_destroy(HASH **q);

//hash API
int hash_func(char * string);
int hash_init(HASH *h);
int hash_destroy(HASH **h);
void hash_print(HASH *h);
int hash_search(HASH *hash, char* string);
int hash_insert(HASH *hash, char* string);
char *get_max_word(HASH *h);
char *get_sec_max_word(HASH *h);
#endif /*   _UTILS_H_ */ 
