#include "trie.h"
#include "../../utils.h"

void create_suffix_tree(char *str, TNODE* root) {
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
    if((*str) && (!searchWholeWordInTrie(root, str)))
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
    TNODE *root=NULL;

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
	    if(searchWholeWordInTrie(root, word)){
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
    TNODE *root = NULL;

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



    if(searchWholeWordInTrie(t, str))
	return 0;

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

/*
 *Given a string, return the length of the longest substring which comprises of consecutive characters.
 *input: xyzdefg
 *Output:
 *4
 *defg
 *
 *Read more: http://javarevisited.blogspot.com/2015/12/30-microsoft-interview-questions-for-software-development-engineers.html#ixzz4exC0Ikad
 *
 *
 *This can be solved by creating a suffix tree of a input string. After that go through all the paths from root to leafs and figuring out the path which has the largest consecutive characters
 */



/*
 *Suppose you are getting Stream of words from upstream: mary, army, tea, java, goog, eat. Build a data structure to store these such that, if a query was made to search a word e.g. army, then it should return all the anagrams as well i.e. mary and army, yarm
 *
 *solution : we modify a trie data structure a bit , tot that we also store anagrams at the leaf node in the form of link list
 *
 *typedef struct TNODE{
 *    char c;
 *    struct TNODE *next[NO_OF_CHARS]
 *    LIST *list; // to store anagrams at the leaf node
 *} TNODE;
 *
 *we parse the input stream  of words one by one , sort the word and insert into the trie, and at the leaf node insert the original node in the list.
 *as we keep on parsing the words , if there is an anagram, it will eventually be added at the same list of last anagram we store at leaf of a trie.
 *Once the data has been inserted, when we query a word, we first sort it and search it in trie. and return the list of the anagrams on the leaf node of that searched word.
 */
int main() {

    TNODE *root = NULL; //root of trie node
    char c;
    char str[256];
    char str1[256];
    TNODE *troot=NULL; 
    int choice, i, len;
    char **board;
    int boardRow, boardCol, wordSize;
    int noOfWords, strLen;
    
    do {
	printf("MENU OPTIONS\n");
	printf("1 -- Insert word in Trie\n");
	printf("2 -- Search whole word in Trie\n");
	printf("3 -- Create a suffix tree\n");
	printf("4 -- Finding the longest repeated substring\n");
	printf("5 -- Find the longest common substring\n");
	printf("6 -- Print all the words in trie\n");
	printf("7 -- Given set of strings, find longest common prefix\n");
	printf("8 -- word search problem\n");
	printf("9 -- substring with Concatenation of All Words\n");
	printf("10 -- count substrings of len k in a string\n");
	printf("11 -- word break problem\n");
	printf("12 -- Search partial word in trie\n");

	
	printf("enter your choice\n");
	scanf("%d", &choice);

	switch(choice) {

	    case 1: 
		printf("Enter the string to be added to trie\n");
		scanf("%s", str);
		root = addWordInTrie(str, root);
		break;
	    case 2: 
		printf("Enter the string\n");
		scanf("%s", str);
		printf("Word %s\n", searchWholeWordInTrie(root, str)?"found":"not found");
		break;

	    case 3:
		printf("Enter the string\n");
		scanf("%s", str);
		str[strlen(str)] = '\0';
		create_suffix_tree(str, troot);

	    case 4:
		/*to  be implemented*/
		break;

	    case 5:
		break;

	    case 6:
	        print_trie(root);
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

            case 12:
		printf("Enter the string\n");
		scanf("%s", str);
		printf("Word %s\n", searchPartialWordInTrie(root, str)?"found":"not found");
		break;

		

	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');

    return 0;
}
