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

/*int main() {*/

    /*char c;*/
    /*char str[256];*/
    /*char str1[256];*/
    /*char *path;*/
    /*TNODE *troot;*/
    /*int choice, i, len;*/
    /*char **board;*/
    /*int boardRow, boardCol, wordSize;*/
    /*int noOfWords, strLen;*/
    
    /*do {*/
	/*printf("MENU OPTIONS\n");*/
	/*printf("1 -- Insert word in Trie\n");*/
	/*printf("2 -- Search word in Trie\n");*/
	/*printf("3 -- Create a suffix tree\n");*/
	/*printf("4 -- Finding the longest repeated substring\n");*/
	/*printf("5 -- Find the longest common substring\n");*/
	/*printf("6 -- Print all the words in trie\n");*/
	/*printf("7 -- Given set of strings, find longest common prefix\n");*/
	/*printf("8 -- word search problem\n");*/
	/*printf("9 -- substring with Concatenation of All Words\n");*/
	/*printf("10 -- count substrings of len k in a string\n");*/
	/*printf("11 -- word break problem\n");*/

	
	/*printf("enter your choice\n");*/
	/*scanf("%d", &choice);*/

	/*switch(choice) {*/

	    /*case 1: */
		/*printf("Enter the string\n");*/
		/*scanf("%s", str);*/
		/*addWordInTrie(str, root);*/
		/*break;*/
	    /*case 2: */
		/*printf("Enter the string\n");*/
		/*scanf("%s", str);*/
		/*printf("Word %s\n", searchWordInTrie(root, str)?"found":"not found");*/
		/*break;*/

	    /*case 3:*/
		/*printf("Enter the string\n");*/
		/*scanf("%s", str);*/
		/*str[strlen(str)] = '\0';*/
		/*create_suffix_tree(str);*/

	    /*case 4:*/
		/*[>to  be implemented<]*/
		/*break;*/

	    /*case 5:*/
		/*break;*/

	    /*case 6:*/
		/*path = (char*)calloc(NO_OF_CHARS, sizeof(char));*/
		/*
		 *To iterate all the words we first go through the dummy nodes and find the first not NULL pointer
		 *and we pass that address to our print routine.
		 */
		/*for(i=0;i<NO_OF_CHARS;i++){*/
		    /*if(root->next[i]){*/
			/*troot = root->next[i];*/
			/*print_words(troot, path, 0);*/
		    /*}*/
		/*}*/
		/*break;*/

	    /*case 7: */
		/*longest_common_prefix(root);*/
		/*break;*/

	    /*case 8:*/
		/*printf("enter board row size\n");*/
		/*scanf("%d", &boardRow);*/
		/*printf("enter board col size\n");*/
		/*scanf("%d", &boardCol);*/
		/*board = create_2Dchar_array(boardRow, boardCol);*/
		/*input_2Dchar_array(board, boardRow, boardCol);*/

		/*printf("enter word size\n");*/
		/*scanf("%d", &wordSize);*/

		/*for(i=0;i<wordSize;i++){*/
		    /*printf("Enter the word\n");*/
		    /*scanf("%s", str);*/
		    /*addWordInTrie(str, root);*/
		/*}*/

		/*find_words(board, boardRow, boardCol, root, wordSize);*/
		/*break;*/

	    /*case 9:*/
		/*find_substring();*/
		/*break;*/

	    /*case 10:*/
		/*printf("Enter the string\n");*/
		/*scanf("%s", str);*/
		/*printf("Enter substring length\n");*/
		/*scanf("%d", &len);*/
		/*count_substrings(str, len);*/
		/*break;*/

	    /*case 11:*/
		/*printf("enter no of words in a dictionary\n");*/
		/*scanf("%d", &noOfWords);*/

		/*printf("enter words\n");*/

		/*for(i=0;i<noOfWords;i++){*/
		    /*scanf("%s", str);*/
		    /*addWordInTrie(str, root);*/
		/*}*/
		/*printf("Enter string\n");*/
		/*scanf("%s", str1);*/

		/*strLen = strlen(str1);*/

		/*printf("%d", word_break(root, str1, 0, strLen-1));*/
		/*break;*/

		

	    /*default:*/
		/*printf("Invalid option\n");*/
		/*break;*/
	/*}*/

    /*}while((c= getchar())!='q');*/

    /*return 0;*/
/*}*/

