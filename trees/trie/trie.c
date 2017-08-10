/*
 *Trie implementation for strings(lowercase only)
 */
#include "../../utils.h"
#include "trie.h"

void initTnode(TNODE* tnode) {
    int i;
    tnode->c = '\0';
    tnode->word_count = 0;
    //make all the pointers to NULL
    for(i=0;i<NO_OF_CHARS;i++){
	tnode->next[i] = NULL;
    }
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

    /*
     *if we dont find the terminating char, it means its not a valid word in trie
     *    though all the chars in the "word" matched the chars in trie
     */
    if(!troot->next[NO_OF_CHARS-1])
	return 0;


    /*update the word count if search is successful*/
    troot->word_count++;
    return 1;
}

/*add node in the trie*/
TNODE* addWordInTrie(char *word, TNODE* troot) {

    TNODE *temp1;
    TNODE *root;

    /*search word in the trie first, if not found add it*/
    if(searchWordInTrie(troot, word))
	return troot;

    //create root, if not created
    if(troot == NULL) {
	troot = createTrieNode();
	/*root = troot; // assign this pointer to global trie root*/
    } 

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

    /*update the word count*/
    troot->word_count++;
    /*
     *once we have added the word, create a node for NULL char
     *this is required if we want to print all the nodes in a trie
     *for ex: to differenciate between words [ foo, food]
     */
    troot->next[NO_OF_CHARS-1] = createTrieNode();

    return root;

}


void print_trie(TNODE* root) {

    int i;
    TNODE *troot = NULL;

    if(!root){
        printf("trie is empty\n");
        return;
    }

    char *path; // array to print all words in trie
    path = (char*)calloc(NO_OF_CHARS, sizeof(char));
    /*
     *To iterate all the words we first go through the dummy nodes and find the first not NULL pointer
     *and we pass that address to our print routine.
     */
    for(i=0;i<NO_OF_CHARS;i++){
        if(root->next[i]){
            troot = root->next[i];
            print_words(troot, path, 0);
        }
    }

}

/*
 *this routine prints all the words in the trie, we use an auxillary array(path) to store the chars 
 *of the trie as we traverse recursively in the trie.
 */

void print_words(TNODE *troot, char *path, int cnt) {

    int i;
    if(!troot->c) {
	printf("%s", path);
	return;
    }
    path[cnt] = troot->c;
    for(i=0;i<NO_OF_CHARS;i++) {
	if(troot->next[i]!=NULL){
	    print_words(troot->next[i], path, ++cnt);

	    /*print the word count, only when the recursion returns from the leaf node*/
	    if(!troot->next[i]->c)
	    printf("[count:%d]\n", troot->word_count);

	    //when the recursion returns, we remove the char from path array
	    path[cnt] = '\0';
	    cnt--;
	}
    }
}




/*
 *leetcode problem 212
https://leetcode.com/problems/word-search-ii/#/description
 *
 *Given a 2D board and a list of words from the dictionary, find all words in the board.
 *
 *Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 *
 *For example,
 *    Given words = ["oath","pea","eat","rain"] and board =
 *
 *    [
 *        ['o','a','a','n'],
 *        ['e','t','a','e'],
 *        ['i','h','k','r'],
 *        ['i','f','l','v']
 *    ]
 */
