
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define EPS 0.000001

/*returns the index of max node between parent,left child and right child*/
int max_node(int a, int b, int c) {

    if((a-b >= 0) && (a-c >=0))
	return a;
    else if(b-a >= 0 && b-c >= 0 )
	return b;
    else 
	return c;
}

int MAX(int a, int b) {
    return (a>b?a:b);
}
int MIN(int a, int b) {
    return (a>b?b:a);
}

void init_array(int *arr, int n){
    int i;
    for(i=0;i<n;i++){
	arr[i] = 1;
    }
}

int* create_1Darray(int n) {
    int *A;
    A = (int*)calloc(n, sizeof(int));

    if(!A)
	return NULL;
    return A;
}
void input_array(int *A, int n) {

    int i;
    for(i=0;i<n;i++){
	scanf("%d", &A[i]);
    }
}

int** create_2Dmatrix(int xlen, int ylen) {
    int i;
    int **T = (int**)calloc(xlen, sizeof(int*));
    for(i=0;i<xlen;i++){
	T[i] = (int*)calloc(ylen, sizeof(int));
    }
    return T;
}

void print_2Dmatrix(int **T, int xlen, int ylen) {

    int i, j;
    for(i=0;i<xlen;i++){
	for(j=0;j<ylen;j++){
	    printf("%d ",T[i][j]);
	}
	printf("\n");
    }
}

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
  *    n	   n-1        n-1
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

int main(){


    char c;
    int choice;
    double num;
    int n1;
    int *A;
    char str[100];
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Square root of a number\n");
	printf("2 -- LCM of an array of intergers(using GCD method)\n");
	printf("3 -- Convert string to int(atoi)\n");
	printf("4 -- Subsets of an array\n");
	printf("5 -- Max area histogram\n");


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
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
