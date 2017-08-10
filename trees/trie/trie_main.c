#include "trie.h"
#include "../../utils.h"

int main() {

    TNODE *root = NULL;
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
