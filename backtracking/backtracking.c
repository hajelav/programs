/*
 *Backtracking 
 *http://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html
 */


/*
 *PRACTICE PROBLEMS FOR BACKTRACKING
 *http://practice.geeksforgeeks.org/tag-page.php?tag=backtracking&isCmp=0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../utils.h"
#include "../trees/trie/trie.h"
#include "../stacks/stack.h"

char * create_string(int len){
    char *str;
    str = (char*)malloc(sizeof(char)*(len+1));
    str[len] = '\0';
    return str;
}

void input_string(char *str) {
    printf("Enter string\n");
    scanf("%s", str);
}

/*
 *permutations of a string
 Time Complexity: O(n*n!)
 */
void string_permutation(char *str, int l, int h) {

    int i;
    if(l==h)
	printf("%s\n", str);

    // for all chars in the string
    for(i=l;i<h;i++){

	swap_str(str, l, i);
	string_permutation(str, l+1, h);
	swap_str(str, l, i);
    }
}


/*
 *leetcode problem 39
 *Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
 *
 *The same repeated number may be chosen from C unlimited number of times.
 *
 *Note:
 *All numbers (including target) will be positive integers.
 *Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
 *The solution set must not contain duplicate combinations.
 *For example, given candidate set 2,3,6,7 and target 7, 
 *    A solution set is: 
 *    [7] 
 *    [2, 2, 3] 
 */

void combination_sum(int *A, int i, int len, STACK *S, int sum){

    int j;

    if(sum == 0){
	print_stack(S);
	return;
    }

    for(j=i;j<len;j++){

	if(A[j] <= sum){
	    push(S, A[j]);
	    combination_sum(A, i, len, S, sum-A[j]);
	    pop(S);
	}
    }
}


/*
 *marbles puzzle :
 *http://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html
 *
 *You have some number n of black marbles and the same number of white marbles, and you have a playing board which consists simply of a line of 2n+1 spaces to put the marbles in. Start with the black marbles all at one end (say, the left), the white marbles all at the other end, and a free space in between.
 *
 *  B   B      W  W
 *  __  __ __  __ __ 
 *
 *  The goal is to reverse the positions of the marbles:
 *
 *  W   W      B  B
 *  __  __ __  __ __ 
 *
 *  The black marbles can only move to the right, and the white marbles can only move to the left (no backing up). At each move, a marble  can either:
 *
 *  Move one space ahead, if that space is clear, or
 *  Jump ahead over exactly one marble of the opposite color, if the space just beyond that marble is clear.
 */



/*
 *http://practice.geeksforgeeks.org/problems/word-boggle/0
 *Given a dictionary, a method to do lookup in dictionary and a M x N board where every cell has one character. Find all possible words that can be formed by a sequence of adjacent characters. Note that we can move to any of 8 adjacent characters, but a word should not have multiple instances of same cell.
 *
 *Example:
 *
 *Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
 *       boggle[][]   = {{'G','I','Z'},
 *                       {'U','E','K'},
 *                       {'Q','S','E'}};
 *
 *Output:  Following words of dictionary are present
 *         GEEKS, QUIZ
 */

int isValid(int i, int j, int R, int C){

    if (i < 0 || j < 0 ||
       i >=R  || j >=C ) 
        return 0;
    return 1;
}

/*this  prints all the combinations of words of all lengths in the 2d array*/
void print_all_possible_words(char **dict, int i, int j, int r, int c, int **visited, STACK *S) {

    if (!isValid(i, j, r, c))
        return; 

    visited[i][j] = 1; // mark the current char as visited
    push(S, dict[i][j]);

    /*step through all the directions*/
    if ((isValid(i-1, j, r, c)) && (!visited[i-1][j]))     //up
        print_all_possible_words(dict, i-1, j, r, c, visited, S);

    if ((isValid(i+1, j, r, c)) && (!visited[i+1][j]))     //down   
        print_all_possible_words(dict, i+1, j, r, c, visited, S);

    if ((isValid(i, j-1, r, c)) && (!visited[i][j-1]))     //left
        print_all_possible_words(dict, i, j-1, r, c, visited, S);

    if ((isValid(i, j+1, r, c)) && (!visited[i][j+1]))     //right
        print_all_possible_words(dict, i, j+1, r, c, visited, S);

    if ((isValid(i-1, j+1, r, c)) && (!visited[i-1][j+1])) 
        print_all_possible_words(dict, i-1, j+1, r, c, visited, S);

    if ((isValid(i-1, j-1, r, c)) && (!visited[i-1][j-1]))
        print_all_possible_words(dict, i-1, j-1, r, c, visited, S);

    if ((isValid(i+1, j-1, r, c)) && (!visited[i+1][j-1]))
        print_all_possible_words(dict, i+1, j-1, r, c, visited, S);

    if ((isValid(i+1, j+1, r, c)) && (!visited[i+1][j+1]))
        print_all_possible_words(dict, i+1, j+1, r, c, visited, S);

    print_stack(S);
    pop(S);
    visited[i][j] = 0;

}

void print_all_valid_words(char **dict, int i, int j, int r, int c, int **visited, STACK *S, TNODE *troot) {

    if (!isValid(i, j, r, c))
        return; 


    push(S, dict[i][j]);

    //search the stack till now, in the trie.If it doesnt match then we dont have to check further
    
    if(!searchPartialWordInTrie(troot, S->arr)){
        pop(S);
        return;
    }

    visited[i][j] = 1; // mark the current char as visited

    /*step through all the directions*/
    if ((isValid(i-1, j, r, c)) && (!visited[i-1][j]))     //up
        print_all_valid_words(dict, i-1, j, r, c, visited, S, troot);

    if ((isValid(i+1, j, r, c)) && (!visited[i+1][j]))     //down   
        print_all_valid_words(dict, i+1, j, r, c, visited, S, troot);

    if ((isValid(i, j-1, r, c)) && (!visited[i][j-1]))     //left
        print_all_valid_words(dict, i, j-1, r, c, visited, S, troot);

    if ((isValid(i, j+1, r, c)) && (!visited[i][j+1]))     //right
        print_all_valid_words(dict, i, j+1, r, c, visited, S, troot);

    if ((isValid(i-1, j+1, r, c)) && (!visited[i-1][j+1])) 
        print_all_valid_words(dict, i-1, j+1, r, c, visited, S, troot);

    if ((isValid(i-1, j-1, r, c)) && (!visited[i-1][j-1]))
        print_all_valid_words(dict, i-1, j-1, r, c, visited, S, troot);

    if ((isValid(i+1, j-1, r, c)) && (!visited[i+1][j-1]))
        print_all_valid_words(dict, i+1, j-1, r, c, visited, S, troot);

    if ((isValid(i+1, j+1, r, c)) && (!visited[i+1][j+1]))
        print_all_valid_words(dict, i+1, j+1, r, c, visited, S, troot);

    /*
     *this will print the stack every time the recursion returns, but the goal here is to 
     *just print the word which is present in the trie, so we just search the whole word
     *in the trie before we print it
     */
    if (searchWholeWordInTrie(troot, S->arr))
        print_stack(S);

    pop(S);
    visited[i][j] = 0;

}
void word_boggle_util(){

    int noOfWords, i, j;
    int r, c;
    int n = 256;
    char *input;
    TNODE *troot = NULL; // node to a trie
    char **dict = NULL;
    int **visited;
    STACK *S;

    printf("Enter the no of words in dictionary\n");
    scanf("%d", &noOfWords);

    input = create_1Dchar_array(n);

    for(i=0;i<noOfWords;i++){
        printf("Enter %d word\n", i);
        input_1Dchar_array(input);
        troot = addWordInTrie(input, troot);
        memset(input, '\0', n);
    }
    print_trie(troot);
    /*
     *printf("enter no of rows for dict\n");
     *scanf("%d", &r);
     *printf("enter no of colc for dict\n");
     *scanf("%d", &c);
     *dict = create_2Dchar_array(r, c);
     *visited = create_2Darray(r, c);
     *printf("fill letters in the dictionary\n");
     *input_2Dchar_array(dict, r, c);
     */
    r = 3;
    c = 3;
    visited = create_2Darray(r, c);
    dict = create_2Dchar_array(r, c);
    memcpy(dict[0], "giz", 3);
    memcpy(dict[1], "uek", 3);
    memcpy(dict[2], "qse", 3);
    print_2Dchar_array(dict, r, c);
    printf("****OUTPUT****\n");

    //initialize the stack of 32
    S = init_stack(32);
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){

           /*prints all combination of words of all lengths , that can be formed by the 2D char array  */
            /*print_all_possible_words(dict, i, j, r, c, visited, S);*/

            /*prints all possible valid words that are present in the trie*/
            print_all_valid_words(dict, i, j, r, c, visited, S, troot);
        }
    }
    free_stack(S);
}



int main() {
    char c;
    int choice, n, sum;
    STACK *S = NULL;
    char *str;
    int *A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- All permutations of a string(backtracking)\n");
	printf("2 -- N Queen problem\n");
	printf("3 -- combination sum problem\n");
	printf("4 -- Words boggle problem\n");


	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter length of string\n");
		scanf("%d", &n);
		str = create_string(n);
		input_string(str);
		printf("Permutations\n");
		string_permutation(str, 0, n);
		break;

	    case 2:
		printf("Enter board length(NXN))\n");
		scanf("%d", &n);
		break;

	    case 3:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);

		printf("enter sum\n");
		    scanf("%d", &sum);

		S = init_stack(32);
		combination_sum(A, 0, n, S, sum);
		

		break;

            case 4:
                word_boggle_util();
		break;

	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
