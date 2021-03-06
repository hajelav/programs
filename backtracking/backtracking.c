/*
 *Backtracking 
 *http://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html
 */


/*
 *PRACTICE PROBLEMS FOR BACKTRACKING
 *http://practice.geeksforgeeks.org/tag-page.php?tag=backtracking&isCmp=0
 */

/*
 *Top 20 questions for backtracking
 *http://www.geeksforgeeks.org/top-20-backtracking-algorithm-interview-questions/
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
    printf("=========OUTPUT=========\n");

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

/*Given an incomplete Sudoku configuration in terms of a 9x9  2-D square matrix (mat[][]) the task to print a solution of the Sudoku. For simplicity you may assume that there will be only one unique solution.

Example
http://practice.geeksforgeeks.org/problems/solve-the-sudoku/0*/



/*this function gets the list of all valid numbers that can be choosen at any index i and j.
as per sudoku rules for any number that can be placed at postion S[i][j]
1. that number shud not be present at entire row
2. that number shud not be present at entire col
3. that number shud not be present in that block of 9 intergers

idea: we maintain a hash ,and check all the numbers in row col and block.after the hash is filled
all the empty slots are the candidates for valid choices to be used*/

typedef struct DATA{
    int *list;
    int size;
}DATA;


DATA* get_valid_numbers_list(int S[][9], int R, int C, int i, int j){

    //declare a hash from 0-9
    int H[10];
    int idx, row, col, start_i, start_j, end_i, end_j;
    int block_i, block_j;
    int l, m;
    int *list;
    DATA *data;
    int count = 0;
    for (idx=0;idx<10;idx++){
        H[idx] = 0;
    }

    //fill the hash with the entire col
    for ( row=0;row < R; row++){
        if(S[row][j] > 0){
            H[S[row][j]] = 1;
        }
    }
    /*print_1Darray(H, 10);*/

    //fill the hash with the entire row
    for ( col=0;col < C; col++){
        if(S[i][col] > 0){
            H[S[i][col]] = 1;
        }
    }
    /*print_1Darray(H, 10);*/
    //fill the hash with the block

    /*the idea is to first find out that which block S[i][j] belong to,
      and then check all i,j in that block to fill the hash*/
    block_i = i/3; 
    block_j = j/3;

    switch(block_i){
        case 0:
            start_i = 0;
            end_i = 2;
            break;
        case 1:
            start_i = 3;
            end_i = 5;
            break;
        case 2:
            start_i = 6;
            end_i = 8;
            break;
    }//switch ends
    switch(block_j){
        case 0:
            start_j = 0;
            end_j = 2;
            break;
        case 1:
            start_j = 3;
            end_j = 5;
            break;
        case 2:
            start_j = 6;
            end_j = 8;
            break;
    }//switch ends

    /*
     *now we have [start_i][start_j] , [end_i][end_j] indices for the block which has S[i][j].
     *fill the hash now
     */

    /*printf("%d %d\n", start_i, start_j);*/
    /*printf("%d %d\n", end_i, end_j);*/
    for(l=start_i;l<= end_i;l++){
        for(m=start_j;m <= end_j;m++){

            if(S[l][m] > 0)
                H[S[l][m]] = 1;
        }
    }
    /*print_1Darray(H, 10);*/

    /*
     *at this point the hash is filled with all rows, cols, and blocks numbers
     *any zeros in the hash is a candidate for valid entry in soduko matrix
     */

    /*printf("List of valid choices for S[%d][%d]\n", i, j);*/
    for(idx=1;idx<10;idx++){
        if(!H[idx])
            count++;
    }

    list = create_1Darray(count);
    count = 0;
    for(idx=1;idx<10;idx++){
        if(!H[idx])
            list[count++] = idx;
    }
    /*print_1Darray(list, count);*/

    data = (DATA*)malloc(sizeof(DATA));
    data->list = list;
    data->size = count;
    
    return data;
}

int sudoku_solver(int S[][9], int row , int col, int R, int C){

    int i, j;
    int k;
    DATA *data;

    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            if(S[i][j] == 0) {
                printf("i=%d, j=%d\n", i , j);
                //get the list of valid numbers for S[i][j]
                data = get_valid_numbers_list(S, R, C, i, j);

                if(data && data->list[0] == 0) {// list is empty, ie no valid choices left at S[i][j]
                    /*printf("%d,%d S[i][j] = %d\n", i, j, S[i][j]);*/
                    /*S[i][j] = 0;*/
                    /*print_1Darray(data->list, data->size);*/
                    return 1;
                }
                //iterate thru the list of valid choices to fill the sudoku matrix
                for(k=0;k<data->size;k++){
                    S[i][j] = data->list[k];
                    if (sudoku_solver(S, i, j, R, C)){
                        S[i][j] = 0;
                    } else {
                        printf("break");
                        /*break;*/
                    }

                }
                free(data->list);
                free(data);
                return 0;
            }
        }
    }
    return 0;
}

void sudoku_solver_util(){

    int S[9][9] = {{3,0,6,5,0,8,4,0,0},
                   {5,2,0,0,0,0,0,0,0},
                   {0,8,7,0,0,0,0,3,1},
                   {0,0,3,0,1,0,0,8,0},
                   {9,0,0,8,6,3,0,0,5},
                   {0,5,0,0,9,0,6,0,0},
                   {1,3,0,0,0,0,2,5,0},
                   {0,0,0,0,0,0,0,7,4},
                   {0,0,5,2,0,6,3,0,0}};

    print_2Darray_static(S, 9, 9);
    sudoku_solver(S, 0, 0, 9, 9);
    printf("\n\n");
    print_2Darray_static(S, 9, 9);
}

/*
 *Word Break Problem using Backtracking
 *Given a valid sentence without any spaces between the words and a dictionary of valid English words, find all possible ways to break the sentence in individual dictionary words.
 *
 *Example
 *
 *Consider the following dictionary 
 *{ i, like, sam, sung, samsung, mobile, ice, 
 *    cream, icecream, man, go, mango}
 *
 *Input: "ilikesamsungmobile"
 *Output: i like sam sung mobile
 *i like samsung mobile
 *
 *Input: "ilikeicecreamandmango"
 *Output: i like ice cream and man go
 *i like ice cream and mango
 *i like icecream and man go
 *i like icecream and mango
 */

void word_break(char *str, int s, int e, TNODE *troot){

    int i;
    if(!str)
        return ;

    if(s > e)
        return ;

    for(i=s;i<=e;i++){

        if(searchWholeWordInTrieUsingIndex(troot, str, s, i)){  
            print_string_index(str, s, i);
            printf("\n");
            /*print_string_index(str, i+1, s);*/
            word_break(str, i+1, e, troot);
            /*print_string_index(str, i+1, s);*/
        }
    }
}

void word_break_util() {

    int i;
    /*char *S = "ilikesamsungmobile";*/
    char *S = "ilikeicecreamandmango";
    char **dict = (char**) malloc((12)*sizeof(char*));
    TNODE *troot = NULL; // create a trie to add the words of the dictionary
    int len;

    dict[0] = "i";
    dict[1] = "like";
    dict[2] = "sam";
    dict[3] = "sung";
    dict[4] = "samsung";
    dict[5] = "mobile";
    dict[6] = "ice";
    dict[7] = "cream";
    dict[8] = "icecream";
    dict[9] = "man";
    dict[10] = "go";
    dict[11] = "mango";
    dict[12] = "and";

    len = strlen(S);

    //add words to trie
    for(i=0;i<13;i++){
        troot = addWordInTrie(dict[i], troot);
    }

    print_trie(troot);
    printf("\n");

    word_break(S, 0, len-1, troot);
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
	printf("5 -- solve the sudoku\n");
	printf("6 -- word break problem using backtracking\n");
	printf("7 -- removing invalid parentheses\n");


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
            case 5:
                sudoku_solver_util();
		break;
            case 6:
                word_break_util();
		break;
            case 7:
                remove_invalid_parentheses_util();
		break;

	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
