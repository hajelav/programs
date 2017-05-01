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

 /*
  *1. for n numbers , we will have 2^n subsets
  *for eg: for n = 4 (1,2,3,4)
  *    total number of subsets = nC0 + nC1 + nC2 + nC3 + nC4
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
 * leetcode problem 200
 * https://leetcode.com/problems/number-of-islands/#/description
 * http://www.careercup.com/question?id=3743299
 *
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically or diagonally. You may assume all four edges of the grid are all surrounded by water.
 *
 * Example 1:
 *
 * 11110
 * 11010
 * 11000
 * 00000
 * Answer: 1
 *
 * Example 2:
 *
 * 11000
 * 11000
 * 00100
 * 00011
 * Answer: 3

 */

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
 *leetcode problem 17
 *https://leetcode.com/problems/letter-combinations-of-a-phone-number/#/description
 *
 *Letter Combinations of a Phone Number
 *
 *2 - abc
 *3 - def
 *4 - ghi
 *5 - jkl
 *.
 *.
 *9 - wxyz
 *
 *Given a digit string, return all possible letter combinations that the number could represent.
 *
 *A mapping of digit to letters (just like on the telephone buttons) is given below.
 *
 *Input:Digit string "23"
 *Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
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

int  capture_regions_util(char **A, int r, int c, int i, int j, char **V) {

    int left,right,up,down;
    if( i>r || i<0 || j<0 || j>r){
        //if the DFS happens to reach here, ie at the boundry of row/col of array 
        return 0;
    }

    /*if we encounter 'x' or have previously visited*/
    if(A[i][j] == 'x' || V[i][j] == 'v')
        return 1;

    //run dfs on all directions only when A[i][j] is not visited and its value is 'o'
    if(V[i][j] != 'v' && (A[i][j] == 'o')){
        V[i][j] = 'v'; //mark as visited
        down = capture_regions_util(A, r, c, i+1,j, V); // go down
        left = capture_regions_util(A, r, c, i,j+1, V); // go left
        up = capture_regions_util(A, r, c, i-1,j, V); // go up
        right = capture_regions_util(A, r, c, i,j-1, V); // go right
    } 

    //if we find that 'o' is surrounded by 'x', then we capture 'o' by replacing it with 'x'
    //ie all  of our left/right/up/down recursive calls have returned 1
    if(left && right && up && down){
        A[i][j] = 'x';
    }

    return (left && right && up && down);
}

void capture_regions() {

    int r, c;
    int i, j;
    char **A;
    char **V;

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
		//run DFS on each island(group of 'o') if its not already visited
                capture_regions_util(A, r-1, c-1, i, j, V);
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



int main() {

    char c;
    int choice;
    double num;
    int n1, n;
    double x;
    int *A;
    char *S, *res;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Square root of a number\n");
	printf("2 -- Subsets of an array\n");
	printf("3 -- Counting no of islands\n");
	printf("4 -- All possible sequences from a number keypad in phone\n");
	printf("5 -- Find how many numbers of length n are there such that each number is at least 4 smaller/greater than the number before and after it.\n");
	printf("6 -- No of ways r objects can be choosen  from n objects(n C r)\n");
	printf("7 -- implement pow function\n");
	printf("8 -- internationalization\n");
	printf("9 -- wildcard\n");
	printf("10 -- permutations of a string\n");
	printf("11 -- capture all regions surrounded by 'X'\n");
	printf("12 -- Walls and gates\n");
	

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
		printf("No of subsets: %d", subset(A, n1));
		free(A);

		break;


	    case 3:
		get_island();
		break;

	    case 4:
		keypad();
		break;


	    case 5:
		number_problem();
		break;
		 
	    case 6:
		combination();
		break;
	    case 7:

		printf("enter x and n\n");
		scanf("%lf%d", &x, &n);
		printf("%lf\n", my_pow_util(x, n));
		break;
	    case 8:
		printf("Enter string len\n");
		scanf("%d", &n);

		printf("Enter string\n");
		S = create_1Dchar_array(n);
		scanf("%s", S);
		i18n(S, 0, n-1, n-1);
		break;

	    case 9:
		printf("Enter string len\n");
		scanf("%d", &n);

		printf("Enter string\n");
		S = create_1Dchar_array(n);
		scanf("%s", S);
		//create a result string to print the path
		res = create_1Dchar_array(n);
		print_wildcard(S, res, 0, n-1);
		break;

	    case 10:
		permutation();
		break;

	    case 11: 
		capture_regions();
		break;

	    case 12:
		walls_and_gates();
		break;

	    default:
		printf("invalid choice\n");
		break;

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
