
/*
 *Ternary search tree implementation for strings(lowercase only)
http://www.drdobbs.com/database/ternary-search-trees/184410528
https://www.youtube.com/watch?v=YYsJGCR4HAY
http://igoro.com/archive/efficient-auto-complete-with-a-ternary-search-tree/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//forward declaration

typedef struct NODE {
	struct TNODE *next;
	char c;
} NODE;

typedef struct TNODE {

     struct NODE node[26]; 
}TNODE;

TNODE *root = NULL;

void initTnode(TNODE* tnode) {
    int i;
    for(i=0;i<26;i++){

	tnode->node[i].next = NULL;
	tnode->node[i].c = '\0';
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


void addWordInTrie(char *word, TNODE* troot) {

    TNODE *temp1;
    //create root, if not created
    if(troot == NULL) {
	troot = createTrieNode();
	root = troot;
    } 

    while(*word!='\0') {

	if(troot->node[*word-'a'].next == NULL) {
	    temp1 = createTrieNode();
	    troot->node[*word - 'a'].next  = temp1; 
	    temp1->node[*word - 'a'].c = *word;
	}
	troot = troot->node[*word-97].next;
	word++;
    }
}

/*search for the word in the trie */
int  searchWordInTrie(TNODE* troot, char *word) {

	if(troot==NULL || word == NULL) {
	    return 0;
	}

    while(*word!='\0') {

	if(troot->node[*word-97].next == NULL) {
	    return 0;
	}
	troot = troot->node[*word-97].next;
	word++;
    }

    return 1;
}

void create_suffix_tree(char *str) {
/*
 * suffix tree can be created just by adding all the suffixes of the string to the trie
 * for eg: bear
 *     	 ear
 *         ar
 *         r
 *
 *         so first we get the suffixes from the string and keep on adding onto the trie
 */
    while(*str!='\0'){
	printf("Adding suffix %s to suffix tree\n", str);
	addWordInTrie(str, root);
	str++;
    }
}


int main() {

    char c;
    char str[256];
    int choice;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Insert word in Trie\n");
	printf("2 -- Search word in Trie\n");
	printf("3 -- Create a suffix tree\n");
	printf("4 -- Finding the longest repeated substring\n");
	printf("5 -- Find the longest common substring\n");
	

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


	}

    }while((c= getchar())!='q');

    return 0;
}
