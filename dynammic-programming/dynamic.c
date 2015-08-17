
//http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
//gcc  minCostPath_recursive.c -Wall -o minCostPath_recursive

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


int MAX(int a, int b) {
    return (a>b?a:b);
}

void init_array(int *arr, int n){
    int i;
    for(i=0;i<n;i++){
	arr[i] = 1;
    }
}

int** create_2Darray(int xlen, int ylen) {
    int i;
    int **T = (int**)calloc(xlen, sizeof(int*));
    for(i=0;i<xlen;i++){
	T[i] = (int*)calloc(ylen, sizeof(int));
    }
    return T;
}

void print_2Darray(int **T, int xlen, int ylen) {

    int i, j;
    for(i=0;i<xlen;i++){
	for(j=0;j<ylen;j++){
	    printf("%d ",T[i][j]);
	}
	printf("\n");
    }
}

/*
 *https://www.youtube.com/watch?v=CE2b_-XfVDk&index=35&list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr
 obtimal substructure :
  let S be the array that stores the LIS 
  L[j] = length of longest subsequence at array len j

  L[j] = Max ( 1 + Max of all the LIS of i ( where 0 < i < j)

 */
int LIS(int *a, int elem) {

    int *S, i, j;
    int max;

    //create an auxillary array to store all the longest increasing subsequence array length at each index i
    S = (int*)malloc(sizeof(int)*elem);

    //initialize all LIS length to 1
    init_array(S, elem);

    for (i=1;i<elem;i++){
        for(j=0;j<i;j++) {
            if(a[j] < a[i]){
		S[i] = MAX(S[i], S[j]+1);
                } 
            } 
        }

    for(i=0;i<elem;i++){
        printf("%d ", S[i]);
    }

    //for the solution, find the max of the array S
    max = 0;
    for(i=0;i<elem;i++) {
        if(S[i] > max){
            max = S[i];
        }
    }

    free(S);
    return max;
}

/*
 *www.8bitavenue.com/2011/12/dynamic-programming-edit-distance/
 *https://www.youtube.com/watch?v=We3YDTzNXEk&list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr&index=25
 *Algorithm : 
 *We compare the last character in each string. We have three possible operations that we can do. The first option is to delete the last character from the first string then convert the remaining characters in the first string to the second string. The second option is to insert the last character from the second string into the end of the first string then convert the first string (before the insertion) into the remaining characters of the second string (excluding the last character). The third option is to replace the last character in the first string with the last character from the second string if they are different otherwise no operation is needed
 */

int MIN(int a, int b, int c) {

    if(a-b <= 0 && a-c <=0)
	return a;
    else if(b-a <= 0 && b-c <= 0 )
	return b;
    else 
	return c;
}
void print_array(int **T, int xlen, int ylen) {

    int i, j;
    for(i=1;i<ylen+1;i++){
	for(j=1;j<xlen+1;j++){
	    printf("%d ",T[i][j]);
	}
	printf("\n");
    }
}

int min_edit_distance(char *X, char *Y) {

    int i,j;

    int xlen, ylen;
    xlen = strlen(X);
    ylen = strlen(Y);
    /* overlapping substructure property
     * let X be of len i (0,1,2 ..... i-1,i)
     * let Y be of len j (0,1,2.......j-1,j)
     * 
     * if(X[i] == Y[j])
     * T[i[]j] (min edit dist from Xi to Yj) = T[i-1][j-1]
     * else {
     * T[i][j] = Min(T[i-1][j-1],  //when Y[j] is obtained after replacing X[i]
     * 		     T[i-1][j],   //when Y[j] is obtained by deleting the last characted of X, ie X[i]
     * 		     T[i][j-1])   //when Y[j] is obtained by inserting the last char of Y into X
     * 		     + 1
     * } */

    
    /*create a min distance arrayi of size m+1 and n+1 to accomodate a null char*/

    int **T = (int**)calloc(ylen+1, sizeof(int*));
    for(i=0;i<ylen+1;i++){
	T[i] = (int*)calloc(xlen+1, sizeof(int));
    }

    /*
     *now initialize the array with the minimum edit distance when each of the string is compared agains NULL char
     */
    for(j=0;j<xlen+1;j++) {
	T[0][j] = j;
    }
    for(i=0;i<ylen+1;i++) {
	T[i][0] = i;
    }

    for(i=1;i<ylen+1;i++) {
	for (j=1;j<xlen+1;j++) {
	    if(X[j-1] == Y[i-1]){  // we do j-1 and i-1 because index of X and Y start with 0
		T[i][j] = T[i-1][j-1];
	    } else {
		T[i][j] = MIN(T[i-1][j], T[i][j-1], T[i-1][j-1]) + 1;
	    }
	}
    }

    print_array(T, xlen, ylen);

    return T[ylen][xlen];
}

/*http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path*/

int min_cost_path(int **A, int r, int c, int posi, int posj) {

    int i,j;
    int **T = (int**)calloc(r+1, sizeof(int*));
    for(i=0;i<r+1;i++){
	T[i] = (int*)calloc(c+1, sizeof(int));
    }

    T[0][0] = 0;

    /*initialize the 0th row and col to INT_MAX*/
    for(i=1;i<r+1;i++) {
	T[i][0] = INT_MAX;
    }
    for(j=1;j<c+1;j++){
	T[0][j] = INT_MAX;
    }

    for(i=1;i<r+1;i++) {
	for (j=1;j<c+1;j++) {
	    T[i][j] = MIN(T[i-1][j], T[i][j-1], T[i-1][j-1]) + A[i-1][j-1]; // optimal substructure property
	}
    }

    print_array(T, r, c);
    return T[posi+1][posj+1];
}

/*
 *http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change
https://www.youtube.com/watch?v=_fgjrs570YE
 *With an infinite supply of given coins, No of ways these coins can be arrange to get a given sum
 */

int coin_change(int *coin, int n, int sum) {

    int i, j;
    int **N;

    /*intialize a 2D array of n+1 rows and sum+1 cols*/

    N = (int**)malloc(sizeof(int*)*n+1);
    for(i=0;i<n+1;i++) {
	N[i] = (int*)malloc(sizeof(int)*(sum+1));
    }

    N[0][0] = 0;
    //initialize all rows for col 0 as zero
    for(i=0;i<n+1;i++){
	N[i][0] = 1;
    }
    for(j=0;j<sum+1;j++){
	N[0][j] = 0;
    }

    for(i=1;i<n+1;i++){
	for(j=1;j<sum+1;j++) {
	
	    //if the denomination of the coin is less than the sum
	    if(coin[i-1] <= j){
		N[i][j] = N[i-1][j] + N[i][j-coin[i-1]];

	    } else {
		N[i][j] = N[i-1][j];
	    }

	}
    }

    //print the N array
    for(i=0;i<n+1;i++){
	for(j=0;j<sum+1;j++) {
	    printf("%d ", N[i][j]);
	}
	printf("\n");
    }

    return N[n][sum];
}


/*
 *https://www.youtube.com/watch?v=8LusJS5-AGo
 *http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/
 *
 *Optimal substructure property:
 *1) Maximum value obtained by n-1 items and W weight (excluding nth item).
 *2) Value of nth item plus maximum value obtained by n-1 items and W minus weight of the nth item (including nth item).
 *
 *If weight of nth item is greater than W, then the nth item cannot be included and case 1 is the only possibility. 
 */

int knapsack(int *wt, int *val, int n, int W) {

    int **T;
    int i, j;
    //create a 2D array of n(no of items) rows and W+1 items
    //this array will store the max values for each weights (from 0...W)
    T = create_2Darray(n, W+1);


    /*
     *before we init the T array, we assume that the wt array is sorted in increasing order of weights
     *we need have all cols before the smallest weight in wt array initialized as zeros as we dont have to consider
      weights which are lower than the min weight. for eg if the wt array is 3,5,6,8 then, then 0,1,2 cols in T will be
      initilized to 0	
     */

    //init the cols which are less than the first elem in wt array with all zeros, ie for weight 0, the max value that can be picked for
    //all items is 0
    for(i=0;i<n;i++) {
	for(j=0;j<wt[0];j++){
	    T[i][j] = 0;
	}
    }

    //initialize first row with with val[0], because when there is only item in tha array then the max value wud be 
    //val[0] for all weights (0....W)
    for(j=wt[0];j<W+1;j++){
	T[0][j] = val[0];
    }

    for(i=1;i<n;i++){ //i items
	for(j=wt[0];j<W+1;j++) { // j weight

	    //if weight of the current item is greater than current weight being considered(col),
	    //then we just inherit from the previous item
	    if(wt[i] > j){
		T[i][j] = T[i-1][j];
	    } else {
		//Max of (max value of i-1 items (excluding ith item) for weight j, value of i item + value of weight left(j-wt[i])) in remainning i-1 items
		T[i][j] = MAX(T[i-1][j], val[i] + T[i-1][j-wt[i]]);

	    }
	}
    }

    //print array
    print_2Darray(T, n, W+1);
    return T[n-1][W];
}

void print_path(int *V, int N){
    int i;
    for(i=0;i<N;i++){
	printf("%d",V[i]);
    }
    printf(" ");
}
void keypad(int **A, int r, int c, int i, int j, int k, int N, int *V) {

    if(i<0||i>=r)
	return;
    if(j<0||j>=c)
	return;
    if((i==r-1 && (j==0 || j==c-1))) 
	return;

    if(k>=N){
	return;
    }

    V[k] = A[i][j];
	keypad(A, r, c, i+1, j, k+1, N, V); //down
	keypad(A, r, c, i-1, j, k+1, N, V); //up
	keypad(A, r, c, i, j-1, k+1, N, V); //left
	keypad(A, r, c, i, j+1, k+1, N, V); //right
	print_path(V, N);
	/*printf("\n");*/
} 

void mob_numeric_keypad(int **A, int r, int c, int N, int *V) { //V -> path array

    int i,j;
    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    if(!(i==r-1 && (j==0 || j==c-1))) {
		keypad(A, r, c, i, j, 0, N, V);
		/*printf("\n");*/
	    }
	}
    }
}

/*
 *https://www.youtube.com/watch?v=3hcaVyX00_4&list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr&index=15
 *given certain number of floors and certain number of eggs, what is the minimum number of attempts(worst case) it takes
 *to find out the floor from which the egg will break

 Optimal Substructure :

 When we drop an egg from a floor x, there can be two cases (1) The egg breaks (2) The egg doesn’t break.
 1) If the egg breaks after dropping from xth floor, then we only need to check for floors lower than x with remaining eggs; so the problem reduces to x-1 floors and n-1 eggs
 2) If the egg doesn’t break after dropping from the xth floor, then we only need to check for floors higher than x; so the problem reduces to k-x floors and n eggs.
 Since we need to minimize the number of trials in worst case, we take the maximum of two cases. We consider the max of above two cases for every floor and choose the floor which yields minimum number of trials. 

 k ==> Number of floors
   n ==> Number of Eggs
     eggDrop(n, k) ==> Minimum number of trails needed to find the critical
                         floor in worst case.
			   eggDrop(n, k) = 1 + min{max(eggDrop(n - 1, x - 1), eggDrop(n, k - x)): 
			                    x in {1, 2, ..., k}}}}
 */
int eggdrop(int e, int f) {

    int i;//eggs
    int j;//floors
    int k; // floors from 1....j
    int min;
    int **N;
    //create array for storing minimum number of ways
    N = create_2Darray(e+1, f+1);

    //when ther is only 1 egg, the no of ways is equal to floors itself
    for(i=1;i<f+1;i++){
	N[1][i] = i;
    }
	
    for(i=2;i<e+1;i++){ //eggs
	for(j=1;j<f+1;j++){ //floors
	    if(i>j) // no of eggs is more than floors , the no of ways = no of floors
		N[i][j] = N[i-1][j];
	    else {

		min = INT_MAX;
		//for all floors starting 1 to J (j included)
		for(k=1;k<=j;k++){
		    if(1+MAX(N[i-1][k-1], N[i][j-k]) < min)
			    min = 1+MAX(N[i-1][k-1], N[i][j-k]);
		}
		N[i][j] = min;
	    }
	}  //floor loop ends
    } //egg loop ends
	
    print_2Darray(N, e+1, f+1);
    return N[e][f];
}

/*
 * https://www.youtube.com/watch?v=_nCsPn7_OgI&list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr&index=19
 *optimal substructure :
 *Let us consider an i, j to be the index of maximum palindromic seq in S.
 *and L be the array for storing the max palidromic seq length
 *
 *S[i],S[i+1]..........S[j-1],S[j] ----> max palindrom seq
 *
 *if(S[i] == S[j] , then 
 *        (max palindrome len from i to j)L[i][j] = L[i+1][j-1] + 2
 *else
 *        L[i][j] = Max(L[i][j-1], L[i+1][j]
 */

int longest_palindromic_seq(char *S) {

    int i, j, k, len, ret;
    int **L;
    len = strlen(S);

    //create a 2D array to store palindromic len
    L = create_2Darray(len, len);
    
    for(i=0;i<len;i++){
	L[i][i] = 1;
    }

    //run the loop diagonally
    for(k=1;k<len;k++){
	for(i=0;(i<len-k);i++){
	    j = i+k;
	    if(S[i] == S[j]){
		L[i][j] = L[i+1][j-1] + 2;
	    } else {
		L[i][j] = MAX(L[i][j-1], L[i+1][j]);
	    }
	}
    }

    print_2Darray(L, len, len);
    ret = L[0][len-1];
    free(L);

    return ret;
}

/*
 *weight interval scheduling problem
 *http://www.careercup.com/question?id=9608562
 */


/*
 *No of ways a number can be added
 *http://www.careercup.com/question?id=12945663
 */

int main(){


    char c;
    int choice;
    int *a, i, j, elem;
    char *X, *Y ;
    int **A, *W, *V;
    int *C, sum; // coins denominations and sum
    int m, n, N; // no of elements in array1 and array2
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Longest Increasing subsequence(LIS)\n");
	printf("2 -- Longest Common subsequence(LCS)\n");
	printf("3 -- Minimum edit distance\n");
	printf("4 -- Minimum cost path\n");
	printf("5 -- Coin change problem\n");
	printf("6 -- 0-1 Knapsack Problem\n");
	printf("7 -- Mobile Numeric Keypad Problem\n");
	printf("8 -- Egg dropping puzzle\n");
	printf("9 -- Longest palindromic subsequence\n");
	printf("10 -- Rod cutting\n");
	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter no of elements\n");
		scanf("%d", &elem);

		a = (int*)malloc(sizeof(int)*elem);
		printf("Enter elements\n");

		for(i=0;i<elem;i++){
		    scanf("%d", &a[i]);
		}
		printf("\nLongest Incresing Subsequence=%d\n", LIS(a, elem));
		free(a);
		break;

	    case 2:
		break;

	    case 3:
		printf("Enter no of elements for array 1\n");
		scanf("%d", &m);

		X = (char*)malloc(sizeof(char)*(m+1));
		X[m] = '\0';
		printf("Enter elements for array 1\n");

		for(i=0;i<m;i++){
		    scanf(" %c", &X[i]);  //space is intentionally added to make scanf work
		}
		printf("Enter no of elements for array 2\n");
		scanf("%d", &n);

		Y = (char*)malloc(sizeof(char)*(n+1));
		Y[n] = '\0';
		printf("Enter elements for array 2\n");

		for(i=0;i<n;i++){
		    scanf(" %c", &Y[i]); // space is intentionally added to make scanf work
		}
		printf("\nMinimum edit distance=%d\n", min_edit_distance(X, Y));
		free(X);
		free(Y);
		break;

	    case 4:
		printf("Enter no of rols and cols in min cost path array\n");
		scanf("%d%d", &m, &n);
		A = (int**)calloc(m, sizeof(int*));
		for(i=0;i<m;i++){
		    A[i] = (int*)calloc(n, sizeof(int));
		}
		printf("Enter elements\n");

		for(i=0;i<m;i++){
		    for(j=0;j<n;j++){
			scanf("%d", &A[i][j]);
		    }
		}
		printf("Enter i,j position\n");
		scanf("%d%d", &i, &j);

		printf("Min cost path : %d\n", min_cost_path(A, m, n, i, j));
		free(A);
		break;

	    case 5:
		printf("Enter the sum\n");
		scanf("%d", &sum);

		printf("Enter the number of coins\n");
		scanf("%d", &n);

		C = (int*)malloc(sizeof(int)*n);

		printf("Enter coin denominations\n");
		for(i=0;i<n;i++){
		    scanf("%d", &C[i]);
		}
		
		printf("\nNo of ways to form Sum(%d) : %d", sum , coin_change(C, n, sum));
		free(C);
		break;

	    case 6:
		printf("Enter knapsack capacity(W)\n");
		scanf("%d", &sum);

		printf("Enter the number of items\n");
		scanf("%d", &n);

		//array to store weights of n items
		W = (int*)malloc(sizeof(int)*n);
		//array to store values of n items
		V = (int*)malloc(sizeof(int)*n);

		printf("Enter weights for %d items\n", n);
		for(i=0;i<n;i++){
		    scanf("%d", &W[i]);
		}
		printf("Enter values for %d items\n", n);
		for(i=0;i<n;i++){
		    scanf("%d", &V[i]);
		}
		printf("Max value that can be picked: %d\n", knapsack(W, V, n, sum));
		break;

	    case 7:
		/*printf("Enter no of rols and cols in min cost path array\n");*/
		/*scanf("%d%d", &m, &n);*/
		m = 4;
		n= 3;
		A = create_2Darray(m, n);
		printf("Enter elements in keypad\n");
		int k=0;
		for(i=0;i<m;i++){
		    for(j=0;j<n;j++){
			/*scanf("%d", &A[i][j]);*/
			if((i==m-1 && (j==0 || j==n-1))) {
			    A[i][j] = -1;

			} else {
			    if(i==m-1 && j==1)
			    A[i][j] = 0;
			    else
			    A[i][j] = ++k;
			}
		    }
		}
		print_2Darray(A, m, n);

		printf("Enter N\n");
		scanf("%d", &N);
		 V = (int*)calloc(N, sizeof(int));

		printf("Path\n");
		mob_numeric_keypad(A, m, n, N, V);
		free(A);
		break;

	    case 8:
		printf("Enter the number of floors\n");
		scanf("%d", &m);
		printf("Enter number of eggs\n");
		scanf("%d", &n);

		printf("Minimum number of trials in worst case with %d eggs and %d floors : %d\n", n, m, eggdrop(n,m));
		break;

	    case 9:
		printf("Enter no of elements for sequence\n");
		scanf("%d", &m);

		X = (char*)malloc(sizeof(char)*(m+1));
		X[m] = '\0';
		printf("Enter string\n");

		for(i=0;i<m;i++){
		    scanf(" %c", &X[i]);  //space is intentionally added to make scanf work
		}
		printf("Longest palidromic sequence : %d\n", longest_palindromic_seq(X));
		break;

	    case 10:
		break;

	    case 11:
		break;
	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
