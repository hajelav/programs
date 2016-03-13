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
    //make all the pointers to NULL
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

/*
 *return 1 if this node is leaf node, else 0,
 *a node is a leaf node only when all next pointer of that trie node are NULL
 */
int isLeaf(TNODE* node) {
    int i;
    for(i=0;i<NO_OF_CHARS;i++){
	if(node->next[i])
	    return 0;
    }
 return 1;
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

TNODE* addWordInTrie(char *word, TNODE* troot) {

    TNODE *temp1, *root;


    /*search word in the trie first, if not found add it*/
    /*
     *if(searchWordInTrie(troot, word))
     *    return;
     */

    //create root, if not created
    if(troot == NULL) {
	troot = createTrieNode();
    } 
	root = troot; // assign this pointer to global trie root

    while(*word!='\0') {

	if(troot->next[*word-'a'] == NULL) {
	    temp1 = createTrieNode();
	    troot->next[*word - 'a']  = temp1; 
	    temp1->c = *word;
	}
	troot = troot->next[*word-'a'];
	word++;
    }

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

	    //when the recursion returns, we remove the char from path array
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

}

