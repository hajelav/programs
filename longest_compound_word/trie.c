/**
 * @file trie.c
 * @brief API for trie data structure
 * @author Vivek Hajela
 * @version 1.0
 * @date 2016-03-14
 */
/*
 *Trie implementation for strings(lowercase only)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

void initTnode(TNODE* tnode) {

    int i;
    tnode->c = '\0';

    /*make all the pointers to NULL*/
    for(i=0;i<NO_OF_CHARS;i++){
	tnode->next[i] = NULL;
    }
    tnode->is_valid_word = 0;
}

TNODE* createTrieNode() {

    TNODE *node;

    node = (TNODE*)malloc(sizeof(TNODE));
    if(node) {
	initTnode(node);
    }
    return node?node:NULL;
}

/*search for the word in the trie */
int  searchWordInTrie(TNODE* troot, char *word) {

    if(troot==NULL || word == NULL || *word == '\0') {
	return 0;
    }

    while(*word!='\0') {
	if(troot->next[*word-'a'] == NULL) {
	    return 0;
	}
	troot = troot->next[*word-'a'];
	word++;
    }
    return 1;
}

/*after pasring words from file, add them to the trie*/
TNODE* addWordInTrie(char *word, TNODE* troot) {

    TNODE *temp1, *root;

    /*search word in the trie first, if not found add it*/
    if(searchWordInTrie(troot, word))
	return NULL;

    /*create root, if not created*/
    if(troot == NULL) {
	troot = createTrieNode();
    } 

    /*save the root pointer to be returned to the caller*/
    root = troot;  

    while(*word!='\0') {

	if(troot->next[*word-'a'] == NULL) {
	    temp1 = createTrieNode();
	    troot->next[*word - 'a']  = temp1; 
	    temp1->c = *word;
	}
	troot = troot->next[*word-'a'];
	word++;
    }

    /*set the flag at the leaf nodes to mark a valid node in trie*/
    troot->is_valid_word = 1;

    /*
     *once we have added the word, create a node for NULL char
     *this is required if we want to print all the nodes in a trie
     *for ex: to differenciate between words [ foo, food]
     */
    troot->next[NO_OF_CHARS-1] = createTrieNode();
    return root;
}

/*
 *this routine prints all the words in the trie, we use an auxillary array(path) to store the chars 
 *of the trie as we traverse recursively in the trie.
 */
void print_words(TNODE *troot, char *path, int cnt) {

    int i;
    if(!troot->c) {
	printf("%s\n", path);
	return;
    }
    path[cnt] = troot->c;
    for(i=0;i<NO_OF_CHARS;i++) {
	if(troot->next[i]!=NULL){
	    print_words(troot->next[i], path, ++cnt);

	    /*/when the recursion returns, we remove the char from path array*/
	    path[cnt] = '\0';
	    cnt--;
	}
    }
}

void print_trie(TNODE *root) {

    int i;
    char *path;
    TNODE *tnode;
    path = (char*)calloc(NO_OF_CHARS, sizeof(char));

    if(!path || !root)
	return;
    /* 
     *To iterate all the words we first go through the dummy nodes and find the first not NULL pointer
     *and we pass that address to our print routine.
     */
    for(i=0;i<NO_OF_CHARS;i++){
	if(root->next[i]){
	    tnode = root->next[i];
	    print_words(tnode, path, 0);
	}
    }
    free(path);
}

void trie_free(TNODE *tnode) {

    int i;
    for(i = 0; i < NO_OF_CHARS; i++)
	if(tnode->next[i])
	    trie_free(tnode->next[i]);
    free(tnode);

}

void trie_destroy(TNODE **troot) {

    if(!troot || *troot)
	return;

    TNODE *root;
    root = *troot;
    trie_free(root);
    *troot = NULL;
}
