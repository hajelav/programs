#include "../utils.h"

#define EPS 0.000001

/*
 *http://codinggeeks.blogspot.com/2010/04/computing-square-cube-roots.html

 solution is based on the binary search
 1. find mid = num/2;
 2. if (mid*mid < num) then sq root lies between mid and number
 3. else sq root lies between 1 and mid
 */
double sqroot(double low, double high, double num) {

    double mid;
    double sqrt;
    if(high < 0)
	return -1;

    mid = (low+high)/2;

    if((mid*mid < num) && (high-low > EPS))
	sqrt = sqroot(mid, high, num);
    else if((mid*mid > num) && (high-low) > EPS) 
	sqrt = sqroot(low, mid, num);
    else 
	sqrt = mid;

    return sqrt;
}

int GCD(int a, int b) {

    int remainder;
    int divisor;
    int temp;

    if(a > b){
	remainder = b%a;
	divisor = a;
    } else{
	remainder = a%b;    
	divisor = b;
    }

    while(remainder > 0){

	temp = remainder;
    	remainder = divisor%remainder;
	divisor = temp;
    }
    return divisor;
}

/*Euclid's Method*/
int  LCM(int a, int b) {

    return (a*b)/GCD(a, b);
}


int find_LCM(int *A, int n) {
    int i, lcm;

    lcm = LCM(A[0], A[1]);
    for(i=2;i<n;i++){
	lcm = LCM(lcm, A[i]);
    }
    return lcm;
}

int get2compliment(int n){
    return (~n+1);
}

/*
 *https://leetcode.com/problems/string-to-integer-atoi/
 *leetcode problem 8
 */
int myatoi(char *str) {

    int len, k;
    int num=0;

    if(!str)
	return 0;

    k = (*str == '-')?1:0;
    len = strlen(str);

    while(k<len) {
	num += pow(10, (len-k-1))*(str[k]-'0');
	k++;
    }

    if(*str == '-'){
	//number is negative
	num = get2compliment(num);

    }
    return num;
}


 /*
  *1. for n numbers , we will have 2^n subsets
  *for eg: for n = 4 (1,2,3,4)
  *    total number of subsets = nC0 + nC1 + nC2 + nC3
  *
  *    using the combination recurrence ( choosing r elements at a time from a set of n elements)
  *    n	n-1        n-1
  *     C  =    C     +   C
  *      r       r-1       r
  *
  *    we can calculate total number of subsets
  *2. one more solution
  *If there are n objects than all 2^n subsets can be determined by iterating from 0 to 2*n and in each iteration by selecting the elements at the position having set bit in the counter.
  *Like for given ex
  *000--{}
  *001--{1}
  *010--{2}
  *011--{2,3}
  *100--{3}
  *101--{1,3}
  *110--{2,3}
  *111--{1,2,3}
  */


void print_subset(int *A, int l, int h) {
    int i;
    for(i=l;i<h;i++){
	printf("%d ", A[i]);
    }
    printf("\n");
}

int subset_util(int *A, int n , int r) {
    int cnt;
    if(r>n || n<1)
	return 0;

    if(n > 0 && r == 0) {
	return 1;
    }
    if(r == n){
	return 1;

    }

    cnt = subset_util(A, n-1, r-1) + subset_util(A, n-1, r);
    return cnt;
}

int subset(int *A , int n) {

    int r, tot_subsets = 0;
    if (n<1)
	return 0;

    for(r=0;r<=n;r++) {
	tot_subsets += subset_util(A, n, r);
    }
    return tot_subsets;
}

/*
 *max area rectangle in a histogram
 *http://tech-queries.blogspot.com/2011/03/maximum-area-rectangle-in-histogram.html
 *
 *H - array of heights of each bar
 *n - number of elements in histogram
 *1- assume width of each bar
 */

/*using divide and conquer method*/

int get_min_height(int *H, int l, int h) {
    int i;
    int min = INT_MAX;
    for(i=l;i<=h;i++) {
	if(H[i] < min)
	    min = H[i];
    }
return min;
}

int max_area_rect_histogram(int *H, int low, int high) {

	int h1, h2, mid;
	int max;
    if(low>=high){
	return H[low];
    }

	mid = (low+high)/2;

	h1 = max_area_rect_histogram(H, low, mid);
	h2 = max_area_rect_histogram(H, mid+1, high);

	/*max = max_node(h1*(mid-low+1), h2*(high-mid), MIN(h1,h2)*(high-low+1));*/
	max = max_node(h1, h2, get_min_height(H, low, high)*(high-low+1));

	return max;
}

void get_island_util(int **A, int r, int c, int i, int j, int **V, int color) {
    

    if( i>r || i<0)
	return ;
    if(j<0 || j>r)
	return ;
    if(A[i][j] == (!color) || V[i][j] == 1)
	return ;

	    //recurese only when we find the color
	    if(!V[i][j] && (A[i][j] == color)){
		V[i][j] = 1; //mark as visited
		 get_island_util(A, r, c, i+1,j, V, color);
		 get_island_util(A, r, c, i,j+1, V, color);
		 get_island_util(A, r, c, i+1,j+1, V, color);
		 get_island_util(A, r, c, i-1,j, V, color);
		 get_island_util(A, r, c, i,j-1, V, color);
		 get_island_util(A, r, c, i-1,j-1, V, color);
		 get_island_util(A, r, c, i+1,j-1, V, color);
		 get_island_util(A, r, c, i-1,j+1, V, color);
	    } 
}

/*
 * leetcode problem 200
 *http://www.careercup.com/question?id=3743299
 */
void get_island() {

    int r, c, color;
    int i, j;
    int **A, **V;
    int tot_islands = 0;
    printf("Enter no of rows\n");
    scanf("%d", &r);
    printf("Enter no of cols\n");
    scanf("%d", &c);

    A = create_2Dmatrix(r, c);
    input_2Darray(A, r, c);
    print_2Dmatrix(A, r, c);
    V = create_2Dmatrix(r, c);
    init_2Darray(V, r, c , 0);

    printf("Enter color\n");
    scanf("%d", &color);


    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    if (!V[i][j] && A[i][j] == color) {
		//run DFS on each island(group of 1's) if its not already visited
		get_island_util(A, r-1, c-1, i, j, V, color);
		tot_islands += 1;
	    }
	}
    }
    
    printf("tot islands: %d\n", tot_islands);
    free(A);
    free(V);
}

/*
 *water cup puzzle 
 *http://www.careercup.com/question?id=9820788
 TBD
 */

 /*
  *reverse the words from a huge file, with billions of records
  *http://www.careercup.com/question?id=14118790
  */


/*
 *Given a sequence of numbers (34128) and an input map such as a dial pad on a phone (2-&gt;[a,b,c], 3-&gt;[d,e,f], 4-&gt;[g,h,i]) write an algorithm to return all possible words from the sequence. E.g. Input: 232 Output: [ada, adb, adc, aea, aeb, aec, afa, afb, afc, bda, bdb, bdc, bea, beb, bec, bfa, bfb, bfc, cda, cdb, cdc, cea, ceb, cec, cfa, cfb, cfc]  
 */

void keypad_util(char **A, int i, int r, int c, char *str) {
    int j;

    if(i==r) {
	//we print only at the leaves
	printf("%s ", str);
	return;;
    }

    for(j=0;j<c;j++) {
	str[i] = A[i][j];
	keypad_util(A, i+1, r, c, str);
    }
}

/*
 *leetcode problem 17
 *https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 */

void keypad() {

    char **A;
    char *str;
    int c = 3; // each number in a keypad as 3 letters
    int r; // number of digits pressed

    printf("enter number of digits pressed\n");
    scanf("%d", &r);


    /*create a 2D char array to store the letter combinations*/
    A = create_2Dchar_array(r, c);

    input_2Dchar_array(A, r, c);
    print_2Dchar_array(A, r, c);


    str = (char*)malloc(sizeof(char)*(r+1));
    str[r] = '\0';
    keypad_util(A, 0, r, c, str);
}


void permutation_util(char **A, char *V, int r, int c, int i, char *str) {
    int j;

    if(i==r) {
	//we print only at the leaves
	printf("%s ", str);
	return;;
    }

    for(j=0;j<c;j++) {
	if(!V[j]) {
	    V[j] = 1;
	    str[i] = A[i][j];
	    permutation_util(A, V, r, c, i+1, str);
	    V[j] = 0;
	}
    }
}

void permutation() {

    char **A;
    char *str; //storing the path 
    char *V; // array to remember visited node 
    int r; //length of string

    printf("enter string length\n");
    scanf("%d", &r);


    A = create_2Dchar_array(r, r);
    input_2Dchar_array(A, r, r);
    print_2Dchar_array(A, r, r);


    str = (char*)malloc(sizeof(char)*(r+1));
    str[r] = '\0';
    V = create_1Dchar_array(r);
    permutation_util(A, V, r, r, 0, str);

    free(A);
    free(V);
}

void one_edit_dist() {


}

/*
 *http://www.careercup.com/question?id=5085262709260288
 */
void num_problem_util(char A[][6], int i, int c, int n, char *path, int k) {
    int j;

    if(k==n) {
	//we print only at the leaves
	printf("%s ", path);
	return;;
    }

    for(j=0;j<c;j++) {
	if(A[i][j] != 'x') {
	    path[k] = A[i][j];
	    num_problem_util(A, A[i][j]-'0', c, n, path, k+1);
	}
    }
}

void clear_path(char *path){
    memset(path, '\0', strlen(path)+1);
}
void number_problem() {
   //maintain the state information, ie for each digit we store the number of permissible next digits
   char state[][6] = { {'4', '5', '6', '7', '8', '9'},   // digit 0
   	              {'5', '6', '7', '8', '9', 'x'},    // digit 1
		      {'6', '7', '8', '9', 'x', 'x'},
		      {'7', '8', '9', 'x', 'x', 'x'},
		      {'0', '8', '9', 'x', 'x', 'x'},
   		      {'0', '1', '9', 'x', 'x', 'x'},
		      {'0', '1', '2', 'x', 'x', 'x'},
		      {'0', '1', '2', '3', 'x', 'x'},
		      {'0', '1', '2', '3', '4', 'x'},
		      {'0', '1', '2', '3', '4', '5'} }; // digit 9

   /*
    * now we create a path array array to store all the valid combination of the arrays
    * the length of the array will be 6 ( max number of column in state array)
    */

   char *path = (char*)malloc(sizeof(char)*(6+1));
   int n, i;
   printf("Enter length of digits\n");
   scanf("%d", &n);

   //scan through all the number starting from 1 and print valid digit combinations
   for(i=1;i<=9;i++){
       path[0] = '0'+i;
       num_problem_util(state, i, 6, n, path, 1);
       clear_path(path);
   }
}


/*count the number of 1's*/
int get_one_count(int n) {
    int cnt=0;
    while(n>0){
	if(n&1)
	    cnt++;
	n = n>>1;
    }
    return cnt;
}

void print(char *S, int n) {
    int len;
    len = strlen(S)-1;
    while(n>0){
	if(n&1) {
	    printf("%c", S[len]);
	}
	len--;
	n = n>>1;
    }
    printf("\n");
}


void combination() {
    int n, r, i;
    char *str;

    printf("Enter the no of objects\n");
    scanf("%d", &n);

    printf("Enter the no of objects to be selected\n");
    scanf("%d", &r);

    printf("Enter string\n");
    str = create_1Dchar_array(n);
    scanf("%s", str);

    /*go through all the subsets */
    for(i=1;i<pow(2, n);i++) {
	//if the count of one in all numbers between 1 to 2^n is r
	if(get_one_count(i) == r){
	    print(str, i);
	}
    }
    free(str);
}

/*
 *given n rectangles in a 2D plane, represented by its minimum and maximum x and y cordinates,( ie x1, y1 and x2, y2)
 * write a function which returns true if there exists an overlap between any two rectangles
 *
 * Algorithm :  maintain two seperate interval trees for each x and y coordinates , 
 * 	      As you process each rectangle, do an INTERVAL_SEARCH( pg 348, CLRS) on X coordinate and Y coordinates
 *              if you find any any rectangle ( ie x1-x2 and y1-y2) whose both x and y coordinates overlaps with their 
 *              respective interval trees, then return true , else return false
 */


double  my_pow(double x, int n) {

    double temp;
    if(n==0)
	return 1;

    temp = my_pow(x, n/2);
	if(n%2 == 0)
	    return temp*temp;
	else 
	    return x*temp*temp;
}

double my_pow_util(double x, int n) {

    if(x == 0)
	return 0;

    if(n > 0){
	return my_pow(x, n);
    } else {
	return 1/my_pow(x, n);
    }
}

/*
 *internationalization problem
 *http://www.careercup.com/question?id=5733696185303040
 */

void print_i18n(char *S, int i, int j, int n) {

    int k=0;

    while(k<=i){
	printf("%c", S[k]);
	k++;
    }
    printf("%d", j-(i+1));
    while(j<=n){
	printf("%c", S[j]);
	j++;
    }
    printf("\n");
}

void i18n(char *S, int i, int j, int n) {

    if(j-i == 1)
	return;

    print_i18n(S, i, j, n);

    i18n(S, i+1, j, n);
    i18n(S, i, j-1, n);
}

/*
 *wildcard problem [google interview question]
 *http://www.careercup.com/question?id=5759440689037312
 */

void print_wildcard(char *S, char *res, int i, int n) {

    if(i>n){
	/*res[i] = S[i];*/
	printf("%s\n", res);
	return;
    }

    if(S[i]!='?'){
	res[i] = S[i];
	print_wildcard(S, res, i+1, n);

    }else {
	S[i] = '0';
	res[i] = S[i];
	print_wildcard(S, res, i+1, n);
	S[i] = '1';
	res[i] = S[i];
	print_wildcard(S, res, i+1, n);
	S[i] = '?'; //move the string back to the origial character
    }
}

/*
 *snake and ladder problem [google interview question]
 *http://www.geeksforgeeks.org/snake-ladder-problem-2/
 */

/*
 *http://www.careercup.com/question?id=12636664
 *Given 2n points on a circle.find the number of ways to draw n non intersecting chords. [google interview question]
 *
 *can be solved using catalan number : 
 * 
 *Cat_no = 2n	
 *           C * (1/n+1)
 *            n 
 */


/*
 *http://www.careercup.com/question?id=5094709806497792  [google interview question], good question
 *Given an unsorted array of integers, you need to return maximum possible n such that the array consists at least n values greater than or equals to n. Array can contain duplicate values. 
 *Sample input : [1, 2, 3, 4] -- output : 2 
 *Sample input : [900, 2, 901, 3, 1000] -- output: 3
 *
 *Approach 1: O(1) space
 *1. sort the array
 *2. run a loop and check if (A[i] >= n-i) 
 *3. keep a max of all i's such that condition at step 2 is satisfied (O(nlogn))
 *
 *Approach 2 : using augmented BST(CLRS 339)
 *1. create an augmented BST with the array values(A[i]) -> O(n) time
 *2. run a loop , i = 1 to n (order statistics), 
 *    for each node found for ith order statistic , check if n-i >= A[i]
 *    this can be done in logn time. 
 *
 *Approach 3:  using linear selection algorithm(check out the reply by saurabh)
 */



/*
 *http://www.careercup.com/question?id=5104572540387328 [google interview question]
 *Given a sorted array of integers, write a function that will return the number with the biggest number of repetitions. 
 *(Asked to refine the solution to be more efficient)
 *
 *Approach : 
 *
 *1.Start the search from the end of the array
 *2.run a variant of binary search, where you reach to the left most end of the searched element. remember the index(i) of that end and count of that number(n-i)
 *3. Again run a binary search(step 2) with element at index-1, so that you reach till the left end of that number(at index-1)
 *4. Continue this procedure till you reach 0th index.
 *5. return the max of the count caluclated after each binary search
  time complexity : k*O(logn), where k is number of different digits in an array
 */

/*
 *leetcode problem 6
 *https://leetcode.com/problems/zigzag-conversion/
 */
void zigzag(char *S, int nrows) {

    int cols = 0, len, k, block, no_of_blocks;
    int i=0, j=0;
    int zigzag;
    char **str;

    if(!S || nrows<0)
	return;

    len = strlen(S);

    /*if there is only one element in the string, then just print that element*/
    if(len < 1){
	printf("%s\n", S);
	return;
    }

    /*get the cols of the new array which will be used to print the zigzag order*/

   if(len > nrows) {

    block = (nrows + nrows-2);
    no_of_blocks = len/block;
    cols = no_of_blocks*(nrows-1);

    if(len%block > nrows)
	cols = cols+2;
    else
	cols = cols+1;

   }else {
       cols = 1;
   }
    
    printf("colums: %d\n", cols);

    str = create_2Dchar_array(nrows, cols);
    /*print_2Dchar_array(str, nrows, cols);*/
    /*str = create_2Dchar_array(20, 20);*/

    k = 0;
    /*zigzag = nrows - 1;*/
    while(j<cols) {

	if(i< nrows) {
	    while(i<nrows){
		str[i][j] = S[k];
		/*printf("-->%c ", str[i][j]);*/
		k++;
		if(i == nrows-1)
		    zigzag = i-1;
		i++;
	    }
	} else {

	    if(zigzag > 0) {
		str[zigzag][j] = S[k];
		/*printf("-->%c ", str[i][j]);*/
		zigzag--;
		k++;
	    } 
	    if(zigzag == 0)
		i = 0;
	}
	j++;
    }
    printf("\n");
    print_2Dchar_array(str, nrows, cols);
}

/*
 *leetcode problem 11
 *https://leetcode.com/problems/container-with-most-water/
 complexity : O(n)
Approach : take two pointer(start and end), find min of ( height of start, height of end) 
now maintain the max area = min(H[start], H[end]) * (end-start)
Now 
 */

int maxArea(int* H, int heightSize) {

    int start = 0, end = heightSize-1;
    int maxArea = 0;

    while(start < end) {

	if((MIN(H[start], H[end])*(end-start)) > maxArea)
	    maxArea = MIN(H[start], H[end])*(end-start);

	if(H[start] < H[end]){
	    start++;
	} else if(H[start] > H[end]){
	    end--;
	} else {
	    start++; end--;
	}
    }
    return maxArea;
}

/*
 *leetcode problem 26
 *https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 */

void remove_duplicate_sorted_array(int *A, int len) {

    int i=1, j=1;
    if(!A || len <=0)
	return;

    if(len == 1)
	printf("%d\n", A[0]);

    while(j<len) {
	if(A[j] == A[j-1]){
	    j++;
	} else {
	    A[i] = A[j];
	    i++;
	    j++;
	}
    }

    //print till the i+1 place
    print_1Darray(A, i);
}


/*
 *leetcode problem 27
 *https://leetcode.com/problems/remove-element/
 */

void remove_element(int *A, int len, int elem) {

    int i, j, temp;
    if(!A || len <= 0)
	return;

    i = 0;
    j = len-1;

    while(i!=j) {
	if(A[i] == elem && A[j] != elem){
	    temp = A[j];
	    A[j] = A[i];
	    A[i] = temp;
	    i++;
	}
	j--;
    }

    print_1Darray(A, len);
}


/*
 *leetcode problem 121
 *https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
  Idea: we start from the first element and maintain aa local minimum and maximum
  whenever we find that the price differnce is greater than the previously found difference,
  we update the local maxima and minima. If we find that price difference is less than previously found 
  we update the local minimim, if it is less than previously found minimum 
 */

void buy_sell_stock_single(int *A, int len) {

    int i = 0, j = 1;
    int local_min, local_max;
    int max_profit;

    if(!A || len<=0)
	return;

    local_min = local_max = A[0];
    max_profit = local_max - local_min;

    while(j<len) {

	if(A[j]-A[i] > max_profit){
	    max_profit = A[j]-A[i];
	    local_max = A[j];
	    local_min = A[i];
	} else {
	    if(A[j] < local_min){
		i = j; 
	    }
	}

	j++;
    }
    printf("Buy price:%d, Sell Price:%d, Max Profit:%d\n", local_min, local_max, max_profit);
}

/*
 *leetcode problem 122
 *https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
  Idea: In this problem, since we can buy and sell the stock multiple times, that max profit would be 
  sum of all +ve price difference
 */

void buy_sell_stock_multiple(int *A, int len) {

    int i;
    int profit = 0, diff;

    if(!A || len<=0)
	return;

    for(i=1;i<len;i++) {

	diff = A[i]-A[i-1];
	if(diff > 0)
	    profit += diff;
    }
    printf("Max Profit:%d\n", profit);
}

int main() {

    char c;
    int choice;
    double num;
    int n1, n, elem;
    double x;
    int *A;
    char *S, *res;
    char str[100];
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Square root of a number\n");
	printf("2 -- LCM of an array of intergers(using GCD method)\n");
	printf("3 -- Convert string to int(atoi)\n");
	printf("4 -- Subsets of an array\n");
	printf("5 -- Max area histogram\n");
	printf("6 -- Counting no of islands\n");
	printf("7 -- All possible sequences from a number keypad in phone\n");
	printf("8 -- check if a string is palindrome((lowercase and uppercase characters are considered equal -special characters are ignored)\n");
	printf("9 -- check if the two words are one edit away from each other. i.e one word can be formed from another by inserting/ deleting/replacing one character\n");
	printf("10 -- Find how many numbers of length n are there such that each number is at least 4 smaller/greater than the number before and after it.\n");
	printf("11 -- No of ways r objects can be choosen  from n objects(n C r)\n");
	printf("12 -- implement pow function\n");
	printf("13 -- internationalization\n");
	printf("14 -- wildcard\n");
	printf("15 -- permutations of a string\n");
	printf("16 -- zigzag printing of string\n");
	printf("17 -- container with most water\n");
	printf("18 -- Remove Duplicates from Sorted Array\n");
	printf("19 -- Remove all instances of an element from an Array\n");
	printf("20 -- Best time to buy/sell stock(buying and selling is allowed only once)\n");
	printf("21 -- Best time to buy/sell stock(buying and selling is allowed multiple times)\n");

	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter number\n");
		scanf("%lf", &num);
		printf("Square root:%lf\n", sqroot(0, num, num));
		break;

	    case 2:
		printf("Enter no of elements in array\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter elements\n");

		input_array(A, n1);
		printf("LCM: %d", find_LCM(A, n1));
		free(A);
		break;

	    case 3:
		printf("Enter string\n");
		scanf("%s", str);
		printf("Number : %d", myatoi(str));
		break;

	    case 4:
		printf("Enter no of elements in array\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter elements\n");

		input_array(A, n1);
		printf("No of subsets: %d", subset(A, n1));
		free(A);

		break;

	    case 5:
		printf("Enter no of elements in histogram\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter heights of histogram bars\n");
		input_array(A, n1);
		printf("Max of of rectangle : %d\n", max_area_rect_histogram(A, 0, n1-1));
		free(A);
		break;

	    case 6:
		get_island();
		break;

	    case 7:
		keypad();
		break;

	    case 9:
		one_edit_dist();
		break;

	    case 10:
		number_problem();
		break;
		 
	    case 11:
		combination();
		break;
	    case 12:

		printf("enter x and n\n");
		scanf("%lf%d", &x, &n);
		printf("%lf\n", my_pow_util(x, n));
		break;
	    case 13:
		printf("Enter string len\n");
		scanf("%d", &n);

		printf("Enter string\n");
		S = create_1Dchar_array(n);
		scanf("%s", S);
		i18n(S, 0, n-1, n-1);
		break;

	    case 14:
		printf("Enter string len\n");
		scanf("%d", &n);

		printf("Enter string\n");
		S = create_1Dchar_array(n);
		scanf("%s", S);
		//create a result string to print the path
		res = create_1Dchar_array(n);
		print_wildcard(S, res, 0, n-1);
		break;

	    case 15:
		permutation();
		break;
	    case 16:
		printf("Enter string\n");
		scanf("%s", str);
		printf("Enter row length\n");
		scanf("%d", &n);
		zigzag(str, n);
		break;
	    case 17:
		printf("Enter n non-negative integers\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter integers\n");
		input_array(A, n1);
		printf("Max Area : %d\n",maxArea(A, n1));
		free(A);
		break;

	    case 18:
		printf("Enter no of elements in array\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter elements\n");

		input_array(A, n1);
		printf("Output array\n");
		remove_duplicate_sorted_array(A, n1);
		free(A);
		break;

	    case 19:
		printf("Enter no of elements in array\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter elements\n");

		input_array(A, n1);
		printf("Enter element to be removed\n");
		scanf("%d", &elem);
		 
		printf("Output array\n");
		remove_element(A, n1, elem);
		free(A);
		break;

	    case 20:
		printf("Enter no of elements in array\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter stock prices\n");

		input_array(A, n1);
		buy_sell_stock_single(A, n1);
		free(A);
		break;
	    case 21:
		printf("Enter no of elements in array\n");
		scanf("%d", &n1);
		A = create_1Darray(n1);
		printf("Enter stock prices\n");

		input_array(A, n1);
		buy_sell_stock_multiple(A, n1);
		free(A);
		break;

	    default:
		printf("invalid choice\n");
		break;

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
