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
int my_atoi(char *str) {

    int len, k;
    int num=0;

    if(!str)
	return 0;

    k = (*str == '-')?1:0;
    len = strlen(str);

    while(k<len) {
	/*num += pow(10, (len-k-1))*(str[k]-'0');*/
	num = num*10 + str[k]-'0';
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

/*
 *leetcode problem 78
 *https://leetcode.com/problems/subsets/
 */

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
 *max area rectangle in a histogram(width of each bar = 1 unit)
 *http://tech-queries.blogspot.com/2011/03/maximum-area-rectangle-in-histogram.html
 * stack based o(n) solution
 */

int max_area_rectangle_histogram(int *hist, int noOfBars) {

    int stack[noOfBars];
    int stack_top = -1;
    int i, left_idx[noOfBars], right_idx[noOfBars];
    int max_area = INT_MIN;

    if(!hist || noOfBars <=0)
	return (max_area = 0);;

    for(i=0;i<noOfBars;i++){

	//here for each bar, we try to reach to the leftmost bar whose index is less than the index of current bar(i)
	while(stack_top!= -1 && hist[i]<= hist[stack[stack_top]]) {
	    //pop the stack
	    stack[stack_top] = -1;
	    stack_top--;
	}

	//store the distance of leftmost bar index for current bar(i);
	if(stack_top == -1) //if stack is empty
	    left_idx[i] = i-stack_top -1;
	else
	    left_idx[i] = i-stack[stack_top] -1;

	//push the current bar into the stack
	stack[++stack_top] = i;

    }

    /*print_1Darray(left_idx, noOfBars);*/

    /*reset the stack*/
    memset(stack, -1, noOfBars);
    stack_top = -1;

    /*Now calculate the right index for each bar in the histogram*/
    for(i=noOfBars-1;i>=0;i--){

	//here for each bar, we try to reach to the leftmost bar whose index is less than the index of current bar(i)
	while(stack_top!= -1 && hist[i]<= hist[stack[stack_top]]) {
	    //pop the stack
	    stack[stack_top] = -1;
	    stack_top--;
	}

	//store the distance of leftmost bar index for current bar(i);
	if(stack_top == -1) //if stack is empty
	    right_idx[i] = noOfBars-i -1;
	else
	    right_idx[i] = stack[stack_top]-i -1;

	//push the current bar into the stack
	stack[++stack_top] = i;

    }
    printf("\n");
    /*print_1Darray(right_idx, noOfBars);*/

    /*
     *till this point we have filled the left and right indexes of each bar of histogram, we now calculate the
     *the max area for each bar (hist[i] *(left_idx[i] + right_idx[i] + 1) 
     */

    for(i=0;i<noOfBars;i++) {
	if((hist[i] *(left_idx[i] + right_idx[i] + 1)) > max_area)
	    max_area = hist[i] *(left_idx[i] + right_idx[i] + 1);
    }
    return max_area;
}

void get_island_util(int **A, int r, int c, int i, int j, int **V) {

    if( i>r || i<0)
	return;
    if(j<0 || j>c)
	return;
    if(A[i][j] == 0  || V[i][j] == 1)
	return;

    //recurese only when we find the color
    if(!V[i][j] && (A[i][j] == 1)){
	V[i][j] = 1; //mark as visited
	get_island_util(A, r, c, i+1,j, V);
	get_island_util(A, r, c, i,j+1, V);
	/*get_island_util(A, r, c, i+1,j+1, V);*/ //commented to restrict diagonal movement of DFS
	get_island_util(A, r, c, i-1,j, V);
	get_island_util(A, r, c, i,j-1, V);
	/*get_island_util(A, r, c, i-1,j-1, V);*/
	/*get_island_util(A, r, c, i+1,j-1, V);*/
	/*get_island_util(A, r, c, i-1,j+1, V);*/
    } 
}

/*
 * leetcode problem 200
 *http://www.careercup.com/question?id=3743299
 */
void get_island() {

    int r, c;
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

    /*2 D matrix to mark visited*/
    V = create_2Dmatrix(r, c);
    init_2Darray(V, r, c , 0);


    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    if (!V[i][j] && A[i][j] == 1) {
		//run DFS on each island(group of 1's) if its not already visited
		get_island_util(A, r-1, c-1, i, j, V);
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


    //array to print the strings
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
	if(!V[j]) { //if char is already visited, skip it
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

/*
 *leetcode problem 161
 *https://leetcode.com/problems/one-edit-distance/
 */

int one_edit_distance(char *S, char *T) {

    int len_S = 0, len_T = 0;
    int long_len, long_ptr=0, short_ptr=0, count = 0;
    char *long_str, *short_str;
    
    if(!S || !T)
	return 0;

   len_S = strlen(S);
   len_T = strlen(T);

   //if difference between the lengths is more than 1, then return false
   if(MOD(len_S,len_T) > 1)
       return 0;
   
    if(len_S>len_T){
	long_str = S;
	short_str = T;
	long_len = len_S;
    } else {
	long_str = T;
	short_str = S;
	long_len = len_T;
    }

    while(long_ptr < long_len) {
	//we need to move the pointer of the longer string only when we find a mis-match and the two strings have unequal length
	/*if((short_str[short_ptr] != long_str[long_ptr]) && len_S!=len_T){*/
	if((short_str[short_ptr] != long_str[long_ptr])){
	long_ptr++;
	    count++;
	} else {
	    short_ptr++;
	    long_ptr++;
	}
    }

    if(count > 1)
	return 0;
    else 
       return 1;	
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

    printf("Enter the no of objects to be selected out of %d objects\n", n);
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


double my_pow(double x, int n) {

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
	return 1/my_pow(x, 0-n);
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

void remove_all_instance_of_element(int *A, int len, int elem) {

    int i, j, temp;
    if(!A || len <= 0)
	return;

    i = 0;
    j = len-1;

    while(i<j) {
	if(A[i] == elem && A[j] != elem){
	    temp = A[j];
	    A[j] = A[i];
	    A[i] = temp;
	    i++;
	    j--;
	} else if(A[i]!=elem && A[j] == elem) {
	    i++;
	    j--;
	} else if(A[i]!=elem && A[j]!=elem){
	    i++;
	}else {
	    j--;
	}
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

/*
 *void buy_sell_stock_single(int *A, int len) {
 *
 *    int i = 0, j = 1;
 *    int local_min, local_max;
 *    int max_profit;
 *
 *    if(!A || len<=0)
 *        return;
 *
 *    local_min = local_max = A[0];
 *    max_profit = local_max - local_min;
 *
 *    while(j<len) {
 *
 *        if(A[j]-A[i] > max_profit){
 *            max_profit = A[j]-A[i];
 *            local_max = A[j];
 *            local_min = A[i];
 *        } else {
 *            if(A[j] < local_min){
 *                i = j; 
 *            }
 *        }
 *
 *        j++;
 *    }
 *    printf("Buy price:%d, Sell Price:%d, Max Profit:%d\n", local_min, local_max, max_profit);
 *}
 */

void buy_sell_stock_single(int *A, int len) {

    int j = 1;
    int min_so_far, max_profit = 0;

    if(!A || len < 2)
	return;

    min_so_far = A[0];

    while(j<len){

	if(A[j] < min_so_far)
	    min_so_far = A[j];
	else if(A[j]-min_so_far > max_profit)
	    max_profit = A[j]-min_so_far;
	j++;
    }
    printf("Max Profit:%d\n",  max_profit);
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

/*
 *leetcode problem 130
 *https://leetcode.com/problems/surrounded-regions/
 *
 * Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
 *
 * A region is captured by flipping all 'O's into 'X's in that surrounded region.
 *
 * For example,
 *
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 *
 * After running your function, the board should be:
 *
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 */

void capture_regions_util(char **A, int r, int c, int i, int j, char **V, int *captureByX) {

    if( i>r || i<0){
	//if the DFS happens to reach here, ie at the boundry of row of array, we set the flag 
	*captureByX = 1;
	return ;
    }

    if(j<0 || j>r) {
	//if the DFS happens to reach here, ie at the boundry of col of array, we set the flag 
	*captureByX = 1;
	return ;
    }

    if(A[i][j] == 'x' || V[i][j] == 'v')
	return;

    //run dfs on all directions only when A[i][j] is not visited and its value is 'o'
    if(V[i][j] != 'v' && (A[i][j] == 'o')){
	V[i][j] = 'v'; //mark as visited
	capture_regions_util(A, r, c, i+1,j, V, captureByX); // go south
	capture_regions_util(A, r, c, i,j+1, V, captureByX); // go east
	capture_regions_util(A, r, c, i-1,j, V, captureByX); // go north
	capture_regions_util(A, r, c, i,j-1, V, captureByX); // go west
    } 

    //if we find that 'o' is surrounded by 'x', then we capture 'o' by replacing it with 'x'
    if((*captureByX == 0) && (A[i][j] == 'o')){
	A[i][j] = 'x';
    }
}

void capture_regions() {

    int r, c;
    int i, j;
    char **A, **V;
    int captureByX;

    printf("Enter no of rows\n");
    scanf("%d", &r);
    printf("Enter no of cols\n");
    scanf("%d", &c);

    /*input 2D array*/
    A = create_2Dchar_array(r, c);
    input_2Dchar_array(A, r, c);

    printf("Input matrix\n");
    print_2Dchar_array(A, r, c);

    /*2D matrix to mark visited*/
    V = create_2Dchar_array(r, c);
    init_2Dchar_array(V, r, c , '\0');

    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    if (V[i][j] != 'v' && A[i][j] == 'o') {
		captureByX = 0;
		//run DFS on each island(group of 'o') if its not already visited
		capture_regions_util(A, r-1, c-1, i, j, V, &captureByX);
	    }
	}
    }
    
    printf("Output matrix\n");
    print_2Dchar_array(A, r, c);
    free(A);
    free(V);
}


/*
 *leetcode problem 286
 *https://leetcode.com/problems/walls-and-gates/
 */

void walls_and_gates_util(int **A, int r, int c, int i, int j, char **V, int dist) {

    if( i>r || i<0){
	//if the DFS happens to reach here, ie at the row boundry
	return;
    }

    if(j<0 || j>r) {
	//if the DFS happens to reach here, ie at the col boundry
	return;
    }


    if(A[i][j] == 0 || A[i][j] == -1 || V[i][j] == 'v')
	//either we have hit a wall or a gate, so we need to go back
	return;

   if(dist < A[i][j]){
       //when running a DFS, if we find a room with a distance less than the current value, we update it
       A[i][j] = dist;

   }
   
    if(V[i][j] != 'v'){
	V[i][j] = 'v'; //mark as visited
	walls_and_gates_util(A, r, c, i+1,j, V, dist+1); // go south
	walls_and_gates_util(A, r, c, i,j+1, V, dist+1); // go east
	walls_and_gates_util(A, r, c, i-1,j, V, dist+1); // go north
	walls_and_gates_util(A, r, c, i,j-1, V, dist+1); // go west
    }

    //mark as unvisted
    V[i][j] = '\0';

}

void walls_and_gates() {

    int r, c;
    int i, j, dist = 0;
    int **A;
    char **V;

    printf("Enter no of rows\n");
    scanf("%d", &r);
    printf("Enter no of cols\n");
    scanf("%d", &c);

    /*input 2D array*/
    A = create_2Darray(r, c);
    input_2Darray(A, r, c);

    /*2D matrix to mark visited*/
    V = create_2Dchar_array(r, c);
    init_2Dchar_array(V, r, c , '\0');

    printf("Input matrix\n");
    print_2Darray(A, r, c);

    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    if (A[i][j] == 0) {
		/*before we run DFS we mark the node as -2, so that our DFS runs and does not stop for the base case where A[i][j] == 0*/
		A[i][j] = -2; 
		//run DFS on each island(group of 'o') if its not already visited
		walls_and_gates_util(A, r-1, c-1, i, j, V, dist);
		/*once are done with DFS, and updation of distances, we revert back A[i][j] to 0*/
		A[i][j] = 0;
	    }
	}
    }
    printf("Output matrix\n");
    print_2Darray(A, r, c);
    free(A);
}

/*
 *leetcode problem 85
 *https://leetcode.com/problems/maximal-rectangle/
 *logic :
 *
 *1.take an auxillary array equal to the size of the cols in the matrix
 *2. copy the first row in the aux array created in 1
 *3. find the max area of the histogram formed by the values of the aux array
 *4. go the the next row , and whenver you find non zero value in the new row, add that value to the aux array
 *5. repeat step 3 and 4 untill you cover all the rows, and keep an account of max area obtained 
 *6. return the max area 
 */

void maximum_rectangle() {

    int i,j, r, c;
    int **M, *A;
    int max_area;
    printf("Enter no of rows\n");
    scanf("%d", &r);
    printf("Enter no of cols\n");
    scanf("%d", &c);

    M = create_2Dmatrix(r, c);
    input_2Darray(M, r, c);
    print_2Dmatrix(M, r, c);

    //create an aux array of size cols
    A = create_1Darray(c);

    //copy the first row into aux array
    for(j=0;j<c;j++){
	A[j] = M[0][j];
    }

    //calucate the max area of the histogram formed by first row
    max_area = max_area_rectangle_histogram(A, c);

    for(i=1;i<r;i++){
	//copy the row into the aux array
	for(j=0;j<c;j++){
	    if(M[i][j] > 0)
		A[j] += M[i][j];
	    else
		A[j] = M[i][j]; 
	}

	if(max_area_rectangle_histogram(A, c) > max_area)
	    max_area = max_area_rectangle_histogram(A, c);
	print_1Darray(A, c);
    }

    printf("\nMaximum area of rectangle containing all 1's : %d\n", max_area);
}

/*
 *leetcode problem 56
 *https://leetcode.com/problems/merge-intervals/
 also check the solution in interval trees
 */

void merge_overlapping_intervals() {

	/*
         *1.Sort the intervals based on increasing order of 
	 *starting time.
	 *2. Push the first interval on to a stack.
	 *3. For each interval do the following
	 *a. If the current interval does not overlap with the stack 
	 *top, push it.
	 *b. If the current interval overlaps with stack top and ending
	 *time of current interval is more than that of stack top, 
         *update stack top with the ending  time of current interval.
         *4. At the end stack contains the merged intervals. 
	 */
}

/*
 *linkedin
 *you have a long flowerbed in which some of the plots are planted and some are not. However, flowers cannot be planted in adjacent plots - they would compete for water and both would die. Given a flowerbed (represented as an array containing booleans), return if a given number of new flowers can be planted in it without violating the no-adjacent-flowers rule 
 *Sample inputs 
 *
 *Input: 1,0,0,0,0,0,1,0,0 
 *3 => true 
 *4 => false 
 *
 *input: 1,0,0,1,0,0,1,0,0 
 *1 => true 
 *2 => false 
 *
 *input: 0 
 *1 => true 
 *2 => false  
 */

int can_place_flowers() {

    int i, len, no_to_place;
    int max_flowers = 0;
    int *A;

    printf("enter array length\n");
    scanf("%d", &len); 
    printf("enter number of flowers to be placed\n");
    scanf("%d", &no_to_place); 

    if(len < 1 || no_to_place < 1 || len < no_to_place)
	return 0;

    A = create_1Darray(len);
    input_1Darray(A, len);

    for(i=0;i<len;i++){

	if(A[i] == 0){

	    /*
	     *if we are at first element and len of array > 1 and the next element is 0 ||
             *if we are at last element and, just before element is 0
	     *    then can place a flower and decrement is no of flowers to be placed		
	     */
	    if((i==0 && i+1<len && A[i+1]==0) ||
		    (i==len-1 && A[i-1]==0)){
		A[i] = 1; //plot the plant
		no_to_place--;
		max_flowers++;
	    }

	    if(i-1>=0 && i+1<len && A[i-1] == 0 && A[i+1] == 0){
		A[i] = 1; //plot the plant
		no_to_place--;
		max_flowers++; // total flowers that can be placed
	    }
	}
    }

    free(A);
    /*if we find that all the flowers are used, then return true*/
    if(no_to_place>0)
	return 0;
    else
	return 1;
}

/** linkedin
 ** Implement a method which takes an integer array and returns an integer array (of equal size) in
 ** which each element is the product of every number in the input array with the exception of the
 ** number at that index.implement without using division operator
 **
 ** Example:
 **   [3, 1, 4, 2] => [8, 24, 6, 12]
 **/
void self_excluding_product() {

    int *A, *B, len, i, prod; 
    int *before, *after;

    printf("Enter array length\n");
    scanf("%d", &len);
    A = create_1Darray(len);
    input_1Darray(A, len);

    /*create a new array of equal size*/
    B = create_1Darray(len);

    /*
     *create before and after arrays
     *    before array : store the product till index i for each 0<=i<len
     *    after array : store the product till index i, where i=len-1
     */

    
    before = create_1Darray(len);
    after = create_1Darray(len);

    /*fill in before array*/
    prod = 1;
    for(i=0;i<len;i++){
	prod *= A[i];
	before[i] = prod;
    }
    print_1Darray(before, len);

    /*fill in after array*/
    prod = 1;
    for(i=len-1;i>=0;i--){
	prod *= A[i];
	after[i] = prod;
    }
    print_1Darray(after, len);

    /*
     *now value at B[i] = product of all the elements before i and all the elements after i
     *                    before[i-1] X after[i+1]
     */

    for(i=0;i<len;i++){

	if(i==0)
	    B[i] = after[i+1];
	else if(i==len-1)
	    B[i] = before[i-1];
	else
	    B[i] = before[i-1]*after[i+1];
    }

    print_1Darray(B, len);
    free(A);
    free(B);
    free(before);
    free(after);
}

/*
 *given an array of integers, move all zeros towards the from of an array, without disturbing the order of non zero elements.
 *do it in place(ie without using extra memory)
 *    for eg 1 0 2 3 0 6 8 0 5 should become
 *           0 0 0 1 2 3 6 8 5
 */
void move_zeros() {

    int n, start, end;
    int *A;

    printf("enter array len\n");
    scanf("%d", &n);

    A = create_1Darray(n);

    if(!A || n<=0)
	return;

    input_array(A, n);

    /*initialize the start and end pointers to the end of the array*/
    start = n-1;
    end = n-1;

    while(end >=0) {
	if(A[end]!=0){
	    swap(A, start, end);
	    start--;
	    end--;
	} else if(A[end]==0) {
	    end--;
	}
    }
    print_1Darray(A, n);
}

int happy_number(){

    int n, num = 0, digit;
    
    printf("enter number\n");
    scanf("%d", &n);

    while(n!=1){

	while(n){

	    digit = n%10;
	    num = num + digit*digit;
	    n = n/10;
	    printf("+%d*%d+", digit, digit);
	}
	printf("\n");
	n = num;
	num = 0;
	if(n==1)
	    return 1;
	if(n<10)
	    return 0;
    }

    return 0;
}

/*
 *leetcode problem 287
 *https://leetcode.com/problems/find-the-duplicate-number/
 * Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
 *
 * Note:
 *
 *     You must not modify the array (assume the array is read only).
 *     You must use only constant, O(1) extra space.
 *     Your runtime complexity should be less than O(n2).
 *     There is only one duplicate number in the array, but it could be repeated more than once.
 */

int duplicate_number() {
    int n;
    printf("Enter the number\n");
    scanf("%d", &n);
 
return 0;
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
    char str1[100];
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Square root of a number\n");
	printf("2 -- LCM of an array of intergers(using GCD method)\n");
	printf("3 -- Convert string to int(atoi)\n");
	printf("4 -- Subsets of an array\n");
	printf("5 -- maximum area of histogram\n");
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
	printf("22 -- capture all regions surrounded by 'X'\n");
	printf("23 -- Walls and gates\n");
	printf("24 -- maximum size rectangle of all 1's in a matrix\n");
	printf("25 -- merge all overlapping intervals\n");
	printf("26 -- place flowers\n");
	printf("27 -- self excluding product\n");
	printf("28 -- move all zeros of array towards the front without disturbing the order of non zero elements\n");
	printf("29 -- happy number\n");
	printf("30 -- find the duplicate number\n");
	

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
		printf("Number : %d", my_atoi(str));
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
		printf("Max of of rectangle : %d\n", max_area_rectangle_histogram(A, n1));
		free(A);
		break;

	    case 6:
		get_island();
		break;

	    case 7:
		keypad();
		break;

	    case 9:
		printf("Enter string 1\n");
		scanf("%s", str);
		printf("Enter string 2\n");
		scanf("%s", str1);
		printf("One edit distance:%s\n", one_edit_distance(str, str1)?"Yes":"No");
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
		remove_all_instance_of_element(A, n1, elem);
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

	    case 22: 
		capture_regions();
		break;

	    case 23:
		walls_and_gates();
		break;

	    case 24:
		maximum_rectangle();
		break;

	    case 25:
		merge_overlapping_intervals();
		break;

	    case 26:
		printf("can place flowers : %s\n", can_place_flowers()?"yes":"no");;
		break;

	    case 27:
		self_excluding_product();
		break;

	    case 28:
		move_zeros();
		break;

	    case 29:
		printf("happy number : %s\n", happy_number()?"yes":"no");
		break;

	    case 30:
		printf("duplicate number : %d\n", duplicate_number());
		break;

	    default:
		printf("invalid choice\n");
		break;

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
