/*
 *Trie implementation for strings(lowercase only)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//forward declaration
 #define NO_OF_CHARS 27 //note that 27 char is the string termination char

typedef struct TNODE {
    char c;
    struct TNODE *next[NO_OF_CHARS];
}TNODE;

TNODE *root = NULL;

void initTnode(TNODE* tnode) {
    int i;
    tnode->c = '\0';
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

/*return 1 if this node is leaf node, else 0*/
int isLeaf(TNODE* node) {
    int i;
    for(i=0;i<NO_OF_CHARS;i++){
	if(node->next[i])
	    return 0;
    }
 return 1;
}

void addWordInTrie(char *word, TNODE* troot) {

    TNODE *temp1;
    //create root, if not created
    if(troot == NULL) {
	troot = createTrieNode();
	root = troot; // assign this pointer to global root
    } 

    while(*word!='\0') {

	if(troot->next[*word-'a'] == NULL) {
	    temp1 = createTrieNode();
	    troot->next[*word - 'a']  = temp1; 
	    temp1->c = *word;
	}
	troot = troot->next[*word-'a'];
	word++;
    }

    /*
     *once we have added the word, create a node for NULL char
     *this is required if we want to print all the nodes in a trie
     *for ex: to differenciate between words [ foo, food]
     */
    troot->next[NO_OF_CHARS-1] = createTrieNode();
}

/*search for the word in the trie */
int  searchWordInTrie(TNODE* troot, char *word) {

    if(troot==NULL || word == NULL) {
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

void create_suffix_tree(char *str) {
/*
 * suffix tree can be created just by adding all the suffixes of the string to the trie
 * for eg: bear#
 *     	   ear#
 *         ar#
 *         r#
 *         #
 *
 *         so first we get the suffixes from the string and keep on adding onto the trie
 */
    while(*str!='\0'){
	printf("Adding suffix %s to suffix tree\n", str);
	addWordInTrie(str, root);
	str++;
    }
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

/*
 *leetcode problem 14
 *https://leetcode.com/problems/longest-common-prefix/
 */

/*
 *checks if we reach to a node , where we find more than one branches of a trie node, we return NULL
 * otherwise we return the common char
 */
TNODE* check_branch(TNODE *tnode, char *c) {
    int i, count=0;
    TNODE *node = NULL;

    if(!tnode)
	return node;

    for(i=0;i<NO_OF_CHARS;i++){
	if(tnode->next[i]) {

	    if(count == 0){
		*c = tnode->next[i]->c;
		node = tnode->next[i];
	    }

	    count++;
	}
	if(count > 1)
	    return NULL;
    }
    return node;
}

void longest_common_prefix(TNODE* troot) {

    char str[64];
    TNODE *node = troot; 
    char c  = '\0';
    int i = 0;
    memset(str, '\0', sizeof(str));

    while((node = check_branch(node, &c)) != NULL) {
	str[i] = c;
	i++;
	c = '\0';
    }
    printf("Lowest common string: %s\n", str);
}

int main() {

    char c;
    char str[256];
    char *path;
    TNODE *troot;
    int choice, i;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Insert word in Trie\n");
	printf("2 -- Search word in Trie\n");
	printf("3 -- Create a suffix tree\n");
	printf("4 -- Finding the longest repeated substring\n");
	printf("5 -- Find the longest common substring\n");
	printf("6 -- Print all the words in trie\n");
	printf("7 -- Given set of strings, find longest common prefix\n");
	

	printf("enter your choice\n");
	scanf("%d", &choice);

	switch(choice) {

	    case 1: 
		printf("Enter the string\n");
		scanf("%s", str);
		addWordInTrie(str, root);
		break;
	    case 2: 
		printf("Enter the string\n");
		scanf("%s", str);
		printf("Word %s\n", searchWordInTrie(root, str)?"found":"not found");
		break;

	    case 3:
		printf("Enter the string\n");
		scanf("%s", str);
		str[strlen(str)] = '\0';
		create_suffix_tree(str);

	    case 4:
		/*to  be implemented*/
		break;

	    case 5:
		break;

	    case 6:
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
		break;

	    case 7: 
		longest_common_prefix(root);
		break;

	    default:
		printf("Invalid option\n");
		break;


	}

    }while((c= getchar())!='q');

    return 0;
}
