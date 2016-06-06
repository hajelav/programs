/*
 *Trie implementation for strings(lowercase only)
 */
#include "../../utils.h"

//forward declaration
 #define NO_OF_CHARS 27 //note that 27th char is the string termination char

typedef struct TNODE {
    char c;
    int word_count;
    struct TNODE *next[NO_OF_CHARS];
}TNODE;

TNODE *root = NULL;

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
void addWordInTrie(char *word, TNODE* troot) {

    TNODE *temp1;

    /*search word in the trie first, if not found add it*/
    if(searchWordInTrie(troot, word))
	return;

    //create root, if not created
    if(troot == NULL) {
	troot = createTrieNode();
	root = troot; // assign this pointer to global trie root
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

    /*update the word count*/
    troot->word_count++;
    /*
     *once we have added the word, create a node for NULL char
     *this is required if we want to print all the nodes in a trie
     *for ex: to differenciate between words [ foo, food]
     */
    troot->next[NO_OF_CHARS-1] = createTrieNode();
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

/*
 *leetcode problem 212
 *https://leetcode.com/company/airbnb/
 */


void find_words_util(char **board, int boardRow, int boardCol, TNODE *root, char *str, int i, int j, int k) {

    if(i>=boardRow || i<0 || j>=boardCol || j<0)
	return;
    //return if you dont find the word in trie
    if((*str) && (!searchWordInTrie(root, str)))
	return;

    str[k] = board[i][j];

    find_words_util(board, boardRow, boardCol, root, str, i+1, j, k+1); // down
    find_words_util(board, boardRow, boardCol, root, str, i-1, j, k+1); //up
    find_words_util(board, boardRow, boardCol, root, str, i, j-1, k+1); //left
    find_words_util(board, boardRow, boardCol, root, str, i, j+1, k+1); //right
    str[k] = '\0';
    printf("%s\n", str);

}

void find_words(char **board, int boardRow, int boardCol, TNODE *root, int wordSize) {

    int i, j;
    char str[256];
    memset(str, '\0', sizeof(str));

    /*iterate through the board char by char */
    for(i=0;i<boardRow;i++){
	for(j=0;j<boardCol;j++){
	    //search for the char in the board
	    if(root->next[board[i][j]-'a']) {
		find_words_util(board, boardRow, boardCol, root, str, i, j, 0);
		memset(str, '\0', sizeof(str));

	    }
	}
    }
}

/*
 *leetcode problem 30
 *https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 *You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
 *
 *For example, given:
 *s: "barfoothefoobarman"
 *words: ["foo", "bar"]
 *
 *You should return the indices: [0,9].
 *(order does not matter).
 */

void find_substring() {

    int i;
    int start = 0, count=0;
    int noOfWords, wordSize, strLen;
    char * word;
    char str[128];

    printf("enter no of words\n");
    scanf("%d", &noOfWords);

    printf("Enter word size\n");
    scanf("%d", &wordSize);


    printf("Enter words of size %d\n", wordSize);
    for(i=0;i<noOfWords;i++){
	scanf("%s", str);
	addWordInTrie(str, root);
    }

    printf("Enter string\n");
    scanf("%s", str);

    strLen = strlen(str);

    //allocate space for a word
    word = create_1Dchar_array(strLen);

    while(strLen - start >= noOfWords*wordSize) {
	//copy the wordSize bytes from str into the word buffer(temp buffer)
	for(i=0;i<noOfWords;i++) {
	    memcpy(word, str+start, wordSize);
	    //search the word in trie
	    if(searchWordInTrie(root, word)){
		start = start + wordSize;
		count++;
	    } else {
		start++;
		break;
	    }
	}
	//if we have found a substring which matches all the words of the trie
	if(count == noOfWords){
	    //start is pointing to the end index of the words, we need to substract no of words X word size to get to the front index
	    printf("%d\n", start-noOfWords*wordSize);
	    count = 0;
	}
	

    }
    free(word);
}

/*
 *linkedin
 *Given string say ABCGRETCABCG and substring length let us take length as 3, find the count of possible substrings, for example in above string ABC => 2 and BCG => 2 , where CGR and other 3 word length substrings has a count of 1.
 *
 *http://www.careercup.com/question?id=5682825644736512
 */

void count_substrings(char *str, int len_sub) {

    int i, len_str;
    char *temp; // declare a temp array to store the substrings

    if(!str || len_sub < 1)
	return;

    len_str = strlen(str);

    temp = create_1Dchar_array(len_sub);

    /*loop thru all the substrings of length len_sub*/
    for(i=0;i<len_str-len_sub+1;i++){

	//copy the substring into temp array
	strncpy(temp, str+i, len_sub);

	addWordInTrie(temp, root);
    }
    printf("press option 6 to print trie\n");
}

/*
 *leetcode problem 139
 *http://www.geeksforgeeks.org/dynamic-programming-set-32-word-break-problem/
 *Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
 *
 *For example, given
 *s = "leetcode",
 *  dict = ["leet", "code"].
 *  
 *  Return true because "leetcode" can be segmented as "leet code""
 *  http://thenoisychannel.com/2011/08/08/retiring-a-great-interview-problem
 */


int  word_break(TNODE *t, char *word, int l, int h) {
    int i, res = 0;
    char str[256];

    memset(str, '\0', 256);
    memcpy(str, word+l,  h-l+1);
    str[h+1] ='\0';
    printf("%s\n",str);



    if(searchWordInTrie(t, str))
	return ;

    else {
	for(i=l;i<=h;i++){

	    res = word_break(t, word, l, i) && word_break(t, word, i+1, h);

	}
	if(res)
	    return res;
	else
	    return 0;
    }

}

int main() {

    char c;
    char str[256];
    char str1[256];
    char *path;
    TNODE *troot;
    int choice, i, len;
    char **board;
    int boardRow, boardCol, wordSize;
    int noOfWords, strLen;
    
    do {
	printf("MENU OPTIONS\n");
	printf("1 -- Insert word in Trie\n");
	printf("2 -- Search word in Trie\n");
	printf("3 -- Create a suffix tree\n");
	printf("4 -- Finding the longest repeated substring\n");
	printf("5 -- Find the longest common substring\n");
	printf("6 -- Print all the words in trie\n");
	printf("7 -- Given set of strings, find longest common prefix\n");
	printf("8 -- word search problem\n");
	printf("9 -- substring with Concatenation of All Words\n");
	printf("10 -- count substrings of len k in a string\n");
	printf("11 -- word break problem\n");

	
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

	    case 8:
		printf("enter board row size\n");
		scanf("%d", &boardRow);
		printf("enter board col size\n");
		scanf("%d", &boardCol);
		board = create_2Dchar_array(boardRow, boardCol);
		input_2Dchar_array(board, boardRow, boardCol);

		printf("enter word size\n");
		scanf("%d", &wordSize);

		for(i=0;i<wordSize;i++){
		    printf("Enter the word\n");
		    scanf("%s", str);
		    addWordInTrie(str, root);
		}

		find_words(board, boardRow, boardCol, root, wordSize);
		break;

	    case 9:
		find_substring();
		break;

	    case 10:
		printf("Enter the string\n");
		scanf("%s", str);
		printf("Enter substring length\n");
		scanf("%d", &len);
		count_substrings(str, len);
		break;

	    case 11:
		printf("enter no of words in a dictionary\n");
		scanf("%d", &noOfWords);

		printf("enter words\n");

		for(i=0;i<noOfWords;i++){
		    scanf("%s", str);
		    addWordInTrie(str, root);
		}
		printf("Enter string\n");
		scanf("%s", str1);

		strLen = strlen(str1);

		printf("%d", word_break(root, str1, 0, strLen-1));
		break;

		

	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');

    return 0;
}

