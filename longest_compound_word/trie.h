#ifndef	_TRIE_H_
#define	_TRIE_H_

#include <stdint.h>
#define NO_OF_CHARS 27 //note that 27th char is the string termination char

typedef struct TNODE {
    struct TNODE *next[NO_OF_CHARS];
    char c;                    
    uint32_t is_valid_word:1;  //mark the end of a valid word
}TNODE;

void initTnode(TNODE* tnode);
TNODE* createTrieNode();
int isLeaf(TNODE* node);
int  searchWordInTrie(TNODE* troot, char *word);
TNODE* addWordInTrie(char *word, TNODE* troot);
void searchInTrie(TNODE *troot, char *word);
void print_trie(TNODE *root);
void trie_destroy(TNODE **root);

#endif /*   _TRIE_H_ */ 
