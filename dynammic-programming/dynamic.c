#include "../utils.h"

/*
 *leetcode problem 300
 *https://leetcode.com/problems/longest-increasing-subsequence/
 *https://www.youtube.com/watch?v=CE2b_-XfVDk&index=35&list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr
 obtimal substructure :
  let S be the array that stores the LIS 
  L[j] = length of longest subsequence at array len j
  L[j] = Max ( 1 + Max of all the LIS of i ( where 0 < i < j), A[i])
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
     * T[i][j] (min edit dist from Xi to Yj) = T[i-1][j-1]
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
		T[i][j] = MIN_three(T[i-1][j], T[i][j-1], T[i-1][j-1]) + 1;
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
	    T[i][j] = MIN_three(T[i-1][j], T[i][j-1], T[i-1][j-1]) + A[i-1][j-1]; // optimal substructure property
	}
    }

    print_array(T, r, c);
    return T[posi+1][posj+1];
}

/*
 *http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change
https://www.youtube.com/watch?v=_fgjrs570YE
https://www.youtube.com/watch?v=ZaVM057DuzE
 *With an infinite supply of given coins, No of ways these coins can be arrange to get a given sum
 */

int coin_change(int *coin, int n, int sum) {

    int i, j;
    int **N;

    /*intialize a 2D array of n+1 rows and sum+1 cols
     * n+1 rows for arbitary 0 denomination coin
     * sum+1 for including sum = 0*/

    N = (int**)malloc(sizeof(int*)*n+1);
    for(i=0;i<n+1;i++) {
	N[i] = (int*)malloc(sizeof(int)*(sum+1));
    }

    N[0][0] = 1;

    //if we have a coin of denomination 0, then we can have only 1 way to to to have 0 as sum for all i(no of coins) 
    for(i=0;i<=n;i++){
	N[i][0] = 1;
    }


    // no of ways the sum j can be formed if we just have one coin of denomination 0
    for(j=0;j<=sum;j++){
	N[0][j] = 0;
    }

    for(i=1;i<=n;i++){
	for(j=1;j<=sum;j++) {
	
	    //if the denomination of the coin is less than the sum
	    if(coin[i-1] <= j){
                /*
	        1. No of ways to exlude the current coin(i) to get sum j = N[i-1][j]
	        2. No of ways to include the current coin = no of ways to include sum(j) - current coin's denomination
                */
		N[i][j] = N[i-1][j] + N[i][j-coin[i-1]];

	    } else {
		N[i][j] = N[i-1][j];
	    }

	}
    }

    //print the N array
    for(i=0;i<=n;i++){
	for(j=0;j<=sum;j++) {
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
 * longest palindromic subsequence
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

/*
 *1--a 2--b ... 26--z given a digit , return the count of the   possible output eg. '1313' --- 4 acac mac mm acm '101' --1 ja cannot discard any digit .
 *http://www.glassdoor.com/Interview/1-a-2-b-26-z-given-a-digit-return-the-count-of-the-possible-output-eg-1313-4-acac-mac-mm-acm-101-1-ja-QTN_785194.htm

 Optimal substructure:

 let Map[] be an array of char to int mapping such that
 
 Map[] = {1, 2, 3, 4, ......, 26}
          a  b  c  d          z

	 Let L[j] denotes the array of no of ways a digit of length j can be represented.

	 L[j] =  1  if (j==1) ie we have only one digit
	         L[j-1] + 1   if the digit formed by Map[j-1]Map[j] < 26 and Map[j-1][j] ! = "01"

 */
void digits(){

    //create a map array
    //TBD

}

/*
 * leetcode problem 53
 *maximum sum contiguos array
 *recurrence
 *
 *Let S be the max sum array such that S[i] be the max sum contiguos sum till i
 *A be the original array
 *
 *recurrence :  
 *
 *S[j] = max(S[j-1]+A[j], A[j])
 */

/*
 *cutting the rod
 *http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/
 *Recurrence:
 *
 *L = rod lengths array
 *P = price array
 *M output array, where M[j] is the max value obtained for length j of rod
 *
 *base case: when the rod len is 1(j==1), then we can only have P[1] as the maximum length
 *
 *Now for any length j of rod , the maximum price(M[j]) that we can get :
 *        Max of ( price of rod of jth len(P[j]) ,  for all lengths less than j( ie 0<i<j) P[i] + M[j-i]
 */


int rod_cutting() {
    int l, p; //prices and 
    int *L; // lengths of rod array
    /*int *P; // price array*/
    /*int *M; // output array(containing max value of a given length of rod*/

    printf("Enter the 'rod length' array length\n");
    scanf("%d", &l);
    L = create_1Darray(l); 
    input_1Darray(L, l);

    printf("Enter the price array length\n");
    scanf("%d", &p);
    /*P = create_1Darray(p); */
    input_1Darray(L, p);

    //create an output array
    /*M  = create_1Darray(p); */

//TBD
 return 0;
   

}

/*
 * leetcode problem 3
 *https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/
 Length of the longest substring without repeating characters
 */

int lengthOfLongestSubstring(char* s) {

    int ptr1 = 0, ptr2, i = 0;
    int max_len = 1, count = 0;
    int hash[26];
    int len;
    //string is NULL, return len as 0
    if (!s)
	return 0;

    len = strlen(s);

    memset(hash, 0, sizeof(hash));
    for(ptr2 =0;ptr2< len; ptr2++){

	if(!hash[s[ptr2]-'a']) {
	    hash[s[ptr2]-'a'] = 1;
	} else {
	    /*memset(haddsh, 0, sizeof(hash));*/
	    while(i <= ptr1){
		hash[i] = 0;
		i++;
	    }
	    hash[s[ptr1]-'a'] = 1;
	    ptr1++;
	}
	    count = ptr2 - ptr1 +1;
	    if(count > max_len)
		max_len = count;
    }
    return max_len;
}

/*
 *leetcode problem 5
 *https://leetcode.com/problems/longest-palindromic-substring/
 *http://www.geeksforgeeks.org/longest-palindrome-substring-set-1/
 */

/*
 *recurrence relation :  O(n2) time complexity
 *L store the lengh of all palidromic substring for the given string S
 *and i and j be any index. Now the longest palidromic subsequence at any i, j
 *
 *L[i][j] =  L[i+1][j-1] + 2 , if S[i] == S[j] and i+1 ... j-1 is a palindrome
 *           else
 *        =   1 
 */

int longest_palindromic_substring(char *S) {

    int i, j, k;
    int **L; // declare a 2D array to store the lengths of palindromes
    int len;

    if(!S)
	return 0;

    len = strlen(S);

    //create a 2D array to store palindromic len
    L = create_2Darray(len, len);
    /*memset(L, 0, sizeof(L));*/
    init_2Darray(L, len, len, 0);

    //all the indices from i to i have len 1
    for(i=0;i<len;i++){
	L[i][i] = 1;
    }


    //run the loop diagonally
    for(j=1;j<len;j++) {

	k=j;	
	for(i=0;i<len && k<len;i++,k++){
	    if(S[i] == S[k] && (S[i+1] == S[k-1])){
		L[i][k] = L[i+1][k-1] + 2;
	    } else {
		L[i][k] = 0;
	    }
	}
    }
    print_2Darray(L, len, len);
    return 0;
}

/*
 *leetcode problem 276
 *https://leetcode.com/problems/paint-fence/
 */

int paint_fence(int fences, int colors) {

    int *ways, i;

    if(fences == 0 || colors == 0)
	return 0;
    if(fences == 1)
	return colors;

    ways = create_1Darray(fences+1);
    if(!ways)
	return 0;

    ways[1] = colors;

    for(i=2;i<=fences;i++){

	ways[i] = ways[i-1]*(colors-1);
    }

    return ways[fences];
}


/*
 *leetcode problem 198
 *https://leetcode.com/problems/house-robber/
logic : 
  let Cash[N] be an array of cash stacked in N house
  let P[N] , where P[j] is the max profit obtained at house j

  max profit for obtained at robbing house j P[j] =  Max ( max profit obtained at robbing house P[j-2] + cash at house j, max profit obtained robbing house P[j-1])
 */

int house_robber(int *cash, int houses) {
    
    int j;
   int  *profit;

    //create a array to store the max profits for each house (where 0 house means no house)
    profit = create_1Darray(houses + 1);

    //for 0th(no house) profit is 0
    profit[0] = 0;
    //if there is only one house, the profit will we cash[0] (ie by just robbing the only house)
    profit[1] = cash[1];

    for(j=2;j<=houses;j++){
	profit[j] = MAX(profit[j-2] + cash[j], profit[j-1]);
    }

    return profit[houses];

}

/*
 *leetcode problem 64
 *https://leetcode.com/problems/minimum-path-sum/
 *
 *Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
 *Note: You can only move either down or right at any point in time.
 */


void min_path_sum() {

    int i, j, result;
    int **grid, **minPath;
    int gridRowSize, gridColSize;

    printf("Enter grid row size\n");
    scanf("%d", &gridRowSize);
    printf("Enter grid col size\n");
    scanf("%d", &gridColSize);

    grid = create_2Darray(gridRowSize, gridColSize);
    input_2Darray(grid, gridRowSize, gridColSize);

    printf("Input grid\n");
    print_2Darray(grid, gridRowSize, gridColSize);

    //create a minPath grid such that minPath[i][j] = min path to reach i row and jth col from 0,0
    /*
     *   Now since we can only move either forward or down, the recurrence relation can be defined as 
     *   minPath[i][j] =  Min( min path to [i-1][j] + grid[i][j], min path to [i][j-1] + grid[i][j])   
     */


    //create a minPath grid
    minPath = create_2Darray(gridRowSize, gridColSize);

    minPath[0][0] = grid[0][0];

    /*initialize the first row of minPath grid. since can either move right or down, so for first row the min*/
    /*path would be the current value + previous value	*/

    for(j=1;j<gridColSize;j++){
	minPath[0][j] = minPath[0][j-1] + grid[0][j];
    }


    /*initialize the first col of minPath grid. since can either move right or down, so for first col the minPath*/
    /*would be the current value + previous value	*/

    for(i=1;i<gridRowSize;i++){
	minPath[i][0] = minPath[i-1][0] + grid[i][0];
    }

    for(i=1;i<gridRowSize;i++){
	for(j=1;j<gridColSize;j++){
	    minPath[i][j] = MIN(minPath[i-1][j] + grid[i][j], minPath[i][j-1] + grid[i][j]);
	}
    }

    printf("Min path grid\n");
    print_2Darray(minPath, gridRowSize, gridColSize);

    result = minPath[gridRowSize-1][gridColSize-1];
    free(grid);
    free(minPath);

    printf("Min path : %d\n", result);

}


/*
 *leetcode problem 62
 *https://leetcode.com/problems/unique-paths/
 *A robot is located at the top-left corner of a m x n grid.
 *
 *The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 *
 *How many possible unique paths are there?
 */

void unique_path_util(int** grid, int gridRowSize, int gridColSize, int i, int j, int* paths) {

    //return if we reach to the boundries of grid
    if(i >= gridRowSize || j>=gridColSize)
	return;

    //we reach the finshline. increment the path count every time we reach here
    if(i == gridRowSize-1 && j == gridColSize-1){
	(*paths)++;
	return;
    }

    //move right
    unique_path_util(grid, gridRowSize, gridColSize, i, j+1, paths);
    //move down
    unique_path_util(grid, gridRowSize, gridColSize, i+1, j, paths);

}

void unique_paths(){

    int **grid;
    int paths = 0;
    int gridRowSize, gridColSize;

    printf("Enter grid row size\n");
    scanf("%d", &gridRowSize);
    printf("Enter grid col size\n");
    scanf("%d", &gridColSize);

    grid = create_2Darray(gridRowSize, gridColSize);
    input_2Darray(grid, gridRowSize, gridColSize);

    unique_path_util(grid, gridRowSize, gridColSize, 0, 0, &paths);

    printf("Total paths : %d\n", paths);

}

/*
 *leetcode problem 63
 *https://leetcode.com/problems/unique-paths-ii/
 */

void unique_path_obstacles_util(int** grid, int gridRowSize, int gridColSize, int i, int j, int* paths) {

    //return if we reach to the boundries of grid or we meet an obstacle
    if(i >= gridRowSize || j>=gridColSize || grid[i][j])
	return;

    //we reach the finshline. increment the path count every time we reach here
    if(i == gridRowSize-1 && j == gridColSize-1){
	(*paths)++;
	return;
    }

    //move right
    unique_path_obstacles_util(grid, gridRowSize, gridColSize, i, j+1, paths);
    //move down
    unique_path_obstacles_util(grid, gridRowSize, gridColSize, i+1, j, paths);

}

void unique_paths_with_obstacles(){

    int **grid;
    int paths = 0;
    int gridRowSize, gridColSize;

    printf("Enter grid row size\n");
    scanf("%d", &gridRowSize);
    printf("Enter grid col size\n");
    scanf("%d", &gridColSize);

    grid = create_2Darray(gridRowSize, gridColSize);
    input_2Darray(grid, gridRowSize, gridColSize);

    unique_path_obstacles_util(grid, gridRowSize, gridColSize, 0, 0, &paths);

    printf("Total paths : %d\n", paths);

}

/*
 *leetcode problem 96
 *https://leetcode.com/problems/unique-binary-search-trees/
 *Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
 *
 *For example,
 *    Given n = 3, there are a total of 5 unique BST's.
 *
 */

int number_of_unique_bst() {

    int i, j, n;
    int *uniqueBSTs;
    printf("Enter the number of nodes in BST\n");
    scanf("%d", &n);

    if(n==0)
	return 0;
    else if(n==1)
	return 1;
    else if(n==2)
	return 2;

    //create an auxillary array to store unique BSTs. The array starts with 0 nodes
    uniqueBSTs = create_1Darray(n+1);
    uniqueBSTs[0] = 1; // for 0 nodes, mark the value as 1 
    uniqueBSTs[1] = 1; // for 1 nodes, there is 1 unique BST
    uniqueBSTs[2] = 2; // for 1 nodes, there is 1 unique BST
    

   /*
    *logic :
    *no of unique BST for any number of nodes j (where i<=j<=n) =  no of unique BST for j-1 nodes * no of unique BST for n-j nodes for all
    *nodes from 1 to n
    */

   for(i=3;i<=n;i++){
       for(j=1;j<=i;j++){
	uniqueBSTs[i] = uniqueBSTs[i] + uniqueBSTs[j-1]*uniqueBSTs[i-j];
       }
   }

   return uniqueBSTs[n];
}

/*
 *leetcode problem 120
 *https://leetcode.com/problems/triangle/
 *https://leetcode.com/discuss/5337/dp-solution-for-triangle
 *
 *logic : A triangle is represented as a 2D array(T) 
 *        let the min sum be represented as array M
 *
 *  M[i] ( min sum at row i) = M[i] +  MIN(T[i-1][j-1], M[i-1][j+1]) + A[i][j] 
 */


/*
 *leetcode problem 256
 *https://leetcode.com/problems/paint-house/
 paint has only three colors, Red Blue Green
 */

int min_cost_paint_houses() {

    int i, j, result, min_cost;
    int **cost, *minCost;
    char color[3] = {'R', 'B', 'G'};
    char *painted; // store the last painted house color

    int numOfHouses, numOfColors;

    printf("Enter number of houses\n");
    scanf("%d", &numOfHouses);

    //0 - R, 1 - B, 2 - G
    printf("Enter number of colors(enter 3 for red green blue)\n");
    scanf("%d", &numOfColors);

    cost = create_2Darray(numOfHouses, numOfColors);
    input_2Darray(cost, numOfHouses, numOfColors);

    printf("Input cost array\n");
    print_2Darray(cost, numOfHouses, numOfColors);

    //creat a minCost array to store min cost required to paint jth array(such that no two adjacent houses are painted same color).
    //the final solution of the problem would be minCost[n-1]
    minCost = create_1Darray(numOfHouses);

    //create an auxillary array color to store the color of last house painted in the minCost array.
    painted  = create_1Dchar_array(numOfHouses);

    //initialize the minCost and color array

    //the first element of the min cost array would be min of the first row of cost array( ie min cost of painting house 0)
    minCost[0] = MIN_three( cost[0][0], cost[0][1], cost[0][2]);

    //find out the color of the minCost[0];
    for(j=0;j<numOfColors;j++){
	if(cost[0][j] == minCost[0])
	    painted[0] = color[j];
    }

    /*
     * recurrence relation : O(n) solution
     *
     * minCost[j]( min cost of painting jth house) = minCost[j-1](min cost to paint j-1 house) + cost[i][j] (min cost to paint jth house such that
     *                                                                                               its color is diff from j-1th house				
     */

    for(i=1;i<numOfHouses;i++){

	if(painted[i-1] == 'R') {

	    if(cost[i][1] <= cost[i][2]){
		min_cost = cost[i][1];
		j = 1;
	    } else {
		min_cost = cost[i][2];
		j = 2;
	    }
	}
	else if(painted[i-1] == 'B'){

	    if(cost[i][0] <= cost[i][2]){
		min_cost = cost[i][0];
		j = 0;
	    } else {
		min_cost = cost[i][2];
		j = 2;
	    }
	}
	else {
	    if(cost[i][0] <= cost[i][1]){
		min_cost = cost[i][0];
		j = 0;
	    } else {
		min_cost = cost[i][2];
		j = 1;
	    }
	}
	minCost[i] = minCost[i-1] + min_cost;
	//update the color in painted array
	painted[i] = color[j];
	
	printf("min cost at i(%d):%d(%d+%d)--%c\n", i, minCost[i], minCost[i-1], min_cost, painted[i]);
	
    }

    result = minCost[numOfHouses-1];
    free(cost);
    free(painted);
    free(minCost);

    return result;    

}

/*
 *leetcode problem 265
 *https://leetcode.com/problems/paint-house-ii/
 *paint the house with k colors
 */

void min_cost_paint_houses_k_colors() {

    int i, j, min_cost;
    int **cost, *minCost;
    int *color; 
    /*char *painted; // store the last painted house color*/

    int numOfHouses, numOfColors;

    printf("Enter number of houses\n");
    scanf("%d", &numOfHouses);

    printf("Enter number of colors\n");
    scanf("%d", &numOfColors);

    cost = create_2Darray(numOfHouses, numOfColors);
    printf("Input cost array\n");
    input_2Darray(cost, numOfHouses, numOfColors);

    print_2Darray(cost, numOfHouses, numOfColors);

    //creat a minCost array to store min cost required to paint jth array(such that no two adjacent houses are painted same color).
    //the final solution of the problem would be minCost[n-1]
    minCost = create_1Darray(numOfHouses);

    //create an auxillary array color to store the color of last house painted in the minCost array.
    color  = create_1Darray(numOfHouses);

    //initialize the minCost and color array

    //the first element of the min cost array would be min of the first row of cost array( ie min cost of painting house 0)
    /*minCost[0] = MIN_three( cost[0][0], cost[0][1], cost[0][2]);*/
    minCost[0] = cost[0][0];
    for(j=1;j<numOfColors;j++){
	if(cost[0][j] < minCost[0]){
	    minCost[0] = cost[0][j];
	    color[0] = j; //store the color of the min cost paint for house 0
	}
    }

    //now start from 1st house of the cost array
    for(i=1;i< numOfHouses;i++){
	min_cost = INT_MAX;
	for(j=0;j<numOfColors;j++) {
	    //if we find min cost paint and the color does not match the previosly painted house
	    if(cost[i][j] < min_cost && j!=color[i-1]){
		min_cost = cost[i][j];
		minCost[i] = min_cost + minCost[i-1]; //upate the minCost array by adding with min cost of painting previous house
		/*minCost[i] = min_cost;*/
		color[i] = j;
	    }
	}
    }

    printf("Min cost to paint %d houses with %d colors : %d\n", numOfHouses, numOfColors, minCost[numOfHouses-1]);
    print_1Darray(minCost, numOfHouses);
}


/*
 *leetcode problem 152
 *https://leetcode.com/problems/maximum-product-subarray/
 When the array has only positive elements then the product of all elements will be answer. 
 Problem becomes interesting and complex simultaneously when there are negative elements.

 The way I looked at this problem is as follows.
 You have three choices to make at any position in array.
 1. You can get maximum product by multiplying the current element with 
 maximum product calculated so far.  (might work when current 
 element is positive).

 2. You can get maximum product by multiplying the current element with 
 minimum product calculated so far. (might work when current 
 element is negative).

 3.  Current element might be a starting position for maximum product sub
 array

 so you have to maintain current maximum product and current 
 minimum product.
 */

void maximum_product_subarray() {

    int *A, *maxP, len;
    int j, curr_max_product, curr_min_product, max_product;
    printf("Enter the len of array\n");
    scanf("%d", &len);

    A = create_1Darray(len);
    input_1Darray(A, len);

    //create an auxillary array to store the max product
    maxP = create_1Darray(len);

    curr_max_product = A[0];
    curr_min_product = A[0];
    maxP[0] = A[0];

    for(j=1;j<len;j++){

	curr_max_product = MAX_three(maxP[j-1]*A[j], A[j], curr_min_product*A[j]);
	curr_min_product = MIN_three(maxP[j-1]*A[j], A[j], curr_min_product*A[j]);

	maxP[j] = curr_max_product;
    } 

    //now find the max element in maxP array
    max_product = A[0];
    for(j=1;j<len;j++){
	if(maxP[j] > max_product)
	    max_product = maxP[j];
    }
    printf("Maximum product : %d\n", max_product);
}


/*
 *leetcode problem 221
 *https://leetcode.com/problems/maximal-square/
 */

void maximal_square() {
    /*
     *1) Construct a sum matrix S[R][C] for the given M[R][C].
     *    a)	Copy first row and first columns as it is from M[][] to S[][]
     *    b)	For other entries, use following expressions to construct S[][]
     *    If M[i][j] is 1 then
     *    S[i][j] = min(S[i][j-1], S[i-1][j], S[i-1][j-1]) + 1
     *    Else [> If M[i][j] is 0<]
     *    S[i][j] = 0
     *2) Find the maximum entry in S[R][C]
     *3) Using the value and coordinates of maximum entry in S[i], print 
     *    sub-matrix of M[][]
     */

}

/*
 *leetcode problem 97
 *https://leetcode.com/problems/interleaving-string/
 Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "yahoo",
s2 = "sunnyvale",

When s = "yahoosunnyvale", return true.
When s3 = "yahosunnyvale", return false.
 */

void interleaving_strings() {


}

int get_len(int *wordLen, int i, int j, int lineWidth){
    int k, sum = 0;
    int word_count = 0;
    for (k=i;k<=j;k++){
	sum += wordLen[k];

	if(sum <= lineWidth)
	    //count words from i to j
	    word_count++;
    }

    if(sum >= lineWidth)
	return INT_MAX;
    else
	//get the empty spaces , which is the diff between line width and sum of all chars of words i to words j + number of spaces between words
	return (lineWidth - (sum + word_count-1));
}

void text_justification() {

    int no_of_words;
    int L; //with of the line
    int i,j, len;
    int *wordLen;
    char **A; //input array
    int **C; //cost array to store the cost of string i to string j in one line  
    //int *minCost;
    //int *result;

    printf("enter the number of words\n");
    scanf("%d", &no_of_words);


    A = create_2Dchar_array(no_of_words, 128);
    input_2Dchar_array(A, no_of_words, 128);
    /*print_2Dchar_array(A, no_of_words, 128);*/

    printf("Enter the max width of each line\n");
    scanf("%d", &L);

    /*after entering the words we need to store the lengths of each words */
    wordLen = create_1Darray(no_of_words);

    /*fill the wordLen array with the lenghts of the words*/

    for(i=0;i<no_of_words;i++){
	wordLen[i] = strlen(A[i]);
    }

    /*for(i=0;i<no_of_words;i++){*/
    /*printf("%s - %d\n", A[i], wordLen[i]);*/
    /*}*/

    /*
     * The value C[i][j] indicates the cost to put words from i to j in a single line where i and j are indexes of words in the input sequences. If a sequence of words from i to j cannot fit in a single line, then lc[i][j] is considered infinite (to avoid it from being a part of the solution)
     *build a cost matrix to store the cost of storing the words in one line.
     *cofficient of badness of a text alignment is the sum of squares of empty spaces over all the lines. 
     *the goal is to find an alignment with minimum coff of badness

     *cost of storing a word(i) to word(j) in one line = square(empty spaces) [Note:spaces between words are not considered as empty spaces] 
     */

    C = create_2Darray(no_of_words, no_of_words);

    /*fill the cost array*/
    for(i=0;i<no_of_words;i++){
	for(j=0;j<no_of_words;j++){

	    if(i<=j){
		//get the length of words from i to j in wordLen array
		len = get_len(wordLen, i, j, L);

		/*if the len fits in the line width then store the cost , otherwise mark the cost as infinity*/
		if(len < INT_MAX)
		    C[i][j] = len*len;
		else
		    C[i][j] = len;

	    }
	}
    }
    print_2Darray(C, no_of_words, no_of_words);

    /*
     *once we have the cost array, we create two arrays
     *    1. to store the min cost
     *    2. to store the final result
     */

    //minCost = create_1Darray(no_of_words);
    

    /*take two pointers i and j(point of split), initially set the pointers to the end of array*/
    i = no_of_words;
    j = no_of_words;

    /*
     *recurrence relation :
     *    minCost[i] =  min{ minCost[j] + C[i][j-1]}, where j=i+1 ... len
     */
    


}

/*
 *leetcode problem 44
 *https://leetcode.com/problems/wildcard-matching/
 *wildcard matching

 O(n) solution with O(1) space : http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html
 DP solution[O(m*n) time and O(m*n) space) : below

 let S be string, P be pattern , match be the array storing the result for any length i of string and j of pattern
 ie match[i][j] = 0 or 1 (if 0 to ith char in string matches with 0-jth char in pattern)
 
 if(char at S[i] and P[j] match OR P[j] == '?')
   match[i][j] = match[i-1][j-1]
  if( pattern has '*')
   match[i][j] = match[i-1][j-1] || match[i][j-1] || match[i-1][j] (if any of the result is true, then match[i][j] becomes true)  
 */

int wildcard_matching() {

    char str[128], pat[128];
    char *S, *P;
    int **match; // auxillary array to store intermediate results 
    int str_len, pat_len;
    int i=0, j=0;

    printf("Enter the string to be matched\n");
    scanf("%s", str);

    printf("Enter the pattern containing wildcards\n");
    scanf("%s", pat);

    str_len = strlen(str);
    pat_len = strlen(pat);

    /*create a string and pattern array which starts with the empty string, this is used in the DP solution*/

    S = create_1Dchar_array(str_len+1); //increase len by 1 to accomodate the "" string
    P = create_1Dchar_array(pat_len+1);

    //copy the str and pat into S and P
    for(i=1;i<=str_len;i++){
	S[i] = str[i-1];
    }
    for(i=1;i<=pat_len;i++){
	P[i] = pat[i-1];
    }


    //create an auxillary array match , which will store the the results for any i(in str) and j(in pat)
    match = create_2Darray(str_len+1, pat_len+1);

    match[0][0] = 1; // all other elements of 2D array is initialized to false(0) at the start

    /*
     *initialize the match 2D array,
     *       1. when the pattern is empty, the result would be 0(false) for all chars in the string
     *       2. when the string is empty(""), the result will only be true when pattern has only stars ("*")
     */

    for(j=1;j<=pat_len;j++){

	/*if we find a star in pattern and previous solution returns true */
	if(P[i] == '*' && match[0][j-1] == 1){
	    match[0][j] = 1;
	}
    }


    /*start the loop in match 2D array( i -> string, j-> pattern)*/
    for(i=1;i<=str_len;i++){
	for(j=1;j<=pat_len;j++){

	    if(P[j] == '?' || (S[i] == P[j])){
		match[i][j] = match[i-1][j-1];
	    }

	    if(P[j] == '*') {
		match[i][j] = match[i-1][j-1] || match[i][j-1] || match[i-1][j];
	    } 
	}
    }

    //check the bottom rightmost element, 0-> if widcard does not match, 1-> widcard match
    printf("Widcard match : %d\n", match[str_len][pat_len]);
    return match[str_len][pat_len];

}

/*
 *leetcode problem 91
 *https://leetcode.com/problems/decode-ways/
 F(n) = F(n-1) + F(n-2)     if s[n] is a valid encoding digit and s[n-1]s[n] is also a valid encoding number.

 F(n) = F(n-1)                     if s[n] is a valid encoding digit and s[n-1]s[n] is NOT a valid encoding number.

 F(n) = F(n-2)                     if s[n] is NOT a valid encoding digit and s[n-1]s[n] is  a valid encoding number.

 F(n) = 0                             if s[n] is NOT a valid encoding digit and s[n-1]s[n] is NOT  a valid encoding number.
 Given an encoded message containing digits, determine the total number of ways to decode it.
 For example,
 Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
 The number of ways decoding "12" is 2.
 */
void decode_message() {

    /*assume that there is no consequitive 0s in the message*/
    int msg_len, i;
    char msg[128];
    int *ways;
    char *M;


    printf("Enter message\n");
    scanf("%s", msg);

    msg_len = strlen(msg);

    if(msg_len == 0 && msg[0] == '0')
	return;

    //malloc space for auxillary array(ways) which stores the num of ways msg can be decoded for any len j
    //note the first element of array will be 0 ( ie 0 ways to decode msg of len 0)

    ways = create_1Darray(msg_len + 1);
    M = create_1Dchar_array(msg_len + 1);
    //copy msg into M , such that msg starts from index 1

    memcpy(M+1, msg, msg_len); 

    ways[0] = 1; 
    ways[1] = 1;

    for(i=2;i<=msg_len;i++) {
	//if the number formed by prev and curr char is less than 26
	if((M[i-1]-'0')*10 + (M[i]-'0') <= 26) {
	    ways[i] = ways[i-1] + ways[i-2];
	} else {
	    ways[i] = ways[i-1];
	}
    }

    printf("Number of ways to decode %s : %d\n", msg, ways[msg_len]);
}


/*
 *leetcode problem 139
 *For example, given
 *s = "leetcode",
 *dict = ["leet", "code"].
 *
 *  Return true because "leetcode" can be segmented as "leet code"
 */

int longest_common_subsequence(char *A, int lenA, char *B, int lenB){

    int i, j, result = 0;
    int **LCS; // 2D array to store the longest common subsequence


    //printf("%d %d", lenA, lenB);
    LCS = create_2Darray(lenA+1, lenB+1);

/*
logic : 
    A = a1a2a3....ai..an
    B = b1b2b3b4 .bj....bm

    suppose L(2D array) holds the longest common subsequence of for any i and j

    if A[i] == B[j]
        L[i][j] = L[i-1][j-1] + 1
    else
        L[i][j] = MAX(L[i-1][j], L[i][j-1])
*/
    

/*we have initialized the length of LCS array to be lenA+1 and lenB+1 to accomodate the null string in A and B 
 * the first row and col in LCS will be zero as, the length of longest common subsequnce for null string("") when compared
 * to the any length of other string will always be zero*/


    for(i=0;i<lenA+1;i++){
        LCS[i][0] = 0;
    }
    for(i=0;i<lenB+1;i++){
        LCS[0][i] = 0;
    }


    for(i=1;i<lenA+1;i++){
        for(j=1;j<lenB+1;j++){

            if (A[i-1] == B[j-1])
                LCS[i][j] = LCS[i-1][j-1] + 1;
            else{
                LCS[i][j] = MAX(LCS[i-1][j], LCS[i][j-1]);


            }
        }
    }

    print_2Darray(LCS, lenA+1, lenB+1);
    result = LCS[lenA][lenB];
    //return LCS[lenA][lenB]; // this is the length of max longest common subsequence

    //now we find out the longest common subsequence which has len LCS[lenA][lenB]
    i = lenA;
    j = lenB;

    while(i>0 && j>0){ // loop till we dont reach to the start of LCS array ( ie i=0 and j=0 )

        //check if i,j came from up, left or diagonal

        if(A[i-1] == B[j-1]){  //we reached here from diagonal
                printf("%c ", A[i-1]);
                i--;
                j--;
        } else{
            //if we reach here then , we must have come either from up or left
            if(i-1 > 0 && LCS[i][j] == LCS[i-1][j]) // we came from up
                 i--;
            else if(j-1 > 0 && LCS[i][j] == LCS[i][j-1]) // we came from left
                 j--;
            else{
                 j--;
                 i--;
            }
        }
    }
    
    return result;

}

/*
Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.

Examples: set[] = {3, 34, 4, 12, 5, 2}, sum = 9
Output:  True  //There is a subset (4, 5) with sum 9.

https://www.youtube.com/watch?v=PKLLFEN3HpU
*/

int sum_of_subset(int *set, int sizeOfSet , int sum) {

    int i, j, result = 0;
    int **L; // 2D array, colums(j) are denoted by sum starting with 0, rows(i) are denoted by items in set starting with null set

    /* create a 2D array(including null set and zero sum) to cover all the sums from 0 to sum
     * and all the items in a set inclucling {} to sizeof set
     */


    L = create_2Darray(sizeOfset+1, sum+1);

    Base cases:

    1. the first entry of array L, ie l[0][0] will be 1 , bceause a null set(i=0) can have sum as zero
    2. the first col(j=0), will always be 1 ( 





}

int main(){


    char c;
    int choice;
    int *a, i, j, elem, houses;
    int fences, colors;
    char *X, *Y ;
    int **A, *W, *V;
    int *C, sum; // coins denominations and sum
    int m, n, N; // no of elements in array1 and array2
    char s[256];
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Longest Increasing subsequence(LIS)\n");
	printf("2 -- Longest common subsequence(LCS)\n");
	printf("3 -- Minimum edit distance\n");
	printf("4 -- Minimum cost path\n");
	printf("5 -- Coin change problem\n");
	printf("6 -- 0-1 Knapsack Problem\n");
	printf("7 -- Mobile Numeric Keypad Problem\n");
	printf("8 -- Egg dropping puzzle\n");
	printf("9 -- Longest palindromic subsequence\n");
	printf("10 -- Rod cutting\n");
	printf("11 -- No of ways a digit can be represented\n");
	printf("12 -- Cutting the rod\n");
	printf("13 -- Longest Substring Without Repeating Characters\n");
	printf("14 -- Longest palindromic substring\n");
	printf("15 -- Paint fence problem\n");
	printf("16 -- house robber problem\n");
	printf("17 -- min path sum problem\n");
	printf("18 -- unique paths from start to finish in 2D array\n");
	printf("19 -- unique paths from start to finish in 2D array with obstacles(Enter 1 for obstacles)\n");
	printf("20 -- number of unique Binary Search Trees)\n");
	printf("21 -- decode message problem\n");
	printf("22 -- min cost to paint all the houses(with Red,Blue,Green)\n");
	printf("23 -- maximum product subarray\n");
	printf("24 -- maximal square  problem\n");
	printf("25 -- min cost to paint all the houses(with k colors)\n");
	printf("27 -- wildcard matching\n");
	printf("28 -- text justification problem(word wrap problem)\n");
	printf("29 -- sum of subset problem)\n");
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
		printf("\nLongest Increasing Subsequence=%d\n", LIS(a, elem));
		free(a);
		break;

	    case 2:
		printf("Enter no of elements for array 1\n");
		scanf("%d", &m);
		printf("Enter no of elements for array 2\n");
		scanf("%d", &n);

		X = (char*)malloc(sizeof(char)*(m+1));
		X[m] = '\0';
		printf("Enter elements for array 1\n");

		for(i=0;i<m;i++){
		    scanf(" %c", &X[i]);  //space is intentionally added to make scanf work
		}

		Y = (char*)malloc(sizeof(char)*(n+1));
		Y[n] = '\0';
		printf("Enter elements for array 2\n");

		for(i=0;i<n;i++){
		    scanf(" %c", &Y[i]); // space is intentionally added to make scanf work
		}
		printf("\nlongest common subsequence=%d\n", longest_common_subsequence(X, m, Y, n));
		free(X);
		free(Y);
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
		digits();

	    case 12:
		rod_cutting();
		break;
	    case 13:
		printf("enter string\n");
		scanf("%s", s);
		printf("Length: %d\n", lengthOfLongestSubstring(s));
		break;

	    case 14:
		printf("enter string\n");
		scanf("%s", s);
		printf("Length: %d\n", longest_palindromic_substring(s));

	    case 15:
		printf("Enter no of fences\n");
		scanf("%d", &fences);
		printf("Enter no of colors\n");
		scanf("%d", &colors);
		printf("No of ways to color %d fences with %d colors : %d\n", fences, colors, paint_fence(fences, colors));
		break;

	    case 16:
		    printf("Enter the number of houses\n");
		    scanf("%d", &houses);

		    int *cash;
		    //house array starts with house 0(no house) and cash as 0. The first element has to be be input as 0
		    cash = create_1Darray(houses+1);
		    printf("Enter the cash for each houses\n");
		    input_array(cash, houses+1);
		    printf("max profit by robbing %d houses : %d\n", houses, house_robber(cash, houses));
		     free(cash);
		     break;


		     min_path_sum();
		     break;

	    case 18:
		     unique_paths();
		     break;
	    case 19:
		     unique_paths_with_obstacles();
		     break;

	    case 20:
		     printf("Number of unique BSTs : %d\n", number_of_unique_bst());
		     break;

	    case 21:
		     decode_message();
		     break;

	    case 22:
		     printf("Min cost to paint all houses with Red,Blue,Green: %d\n", min_cost_paint_houses());
		     break;

	    case 23:
		     maximum_product_subarray();
		     break;

	    case 24:
		     maximal_square();
		     break;
	    case 25:
		     /*printf("Min cost to paint all houses with k colors: %d\n", min_cost_paint_houses_k_colors());*/
		     min_cost_paint_houses_k_colors();
		     break;
	    case 26:
		     interleaving_strings();
		     break;
	    case 27:
		     printf("pattern %s\n", wildcard_matching()? "match":"do not match");
		     break;

	    case 28:
		     text_justification();
		     break;
	    case 29:
                     printf("Enter sum\n");
                     scanf("%d", &sum);

                     printf("Enter the number of items in a set\n");
                     scanf("%d", &n);

                     //array to store values of n items
                     V = (int*)malloc(sizeof(int)*n);

                     printf("Enter %d items\n", n);
                     for(i=0;i<n;i++){
                         scanf("%d", &V[i]);
                     }
                     sum_of_subset(V, n, sum);
                     break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    } while((c=getchar())!='q'); 
    return 0;
}
