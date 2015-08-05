
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define EPS 0.000001


int MAX(int a, int b) {
    return (a>b?a:b);
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
 *for n numbers , we will have 2^n subsets
 *for eg: for n = 4 (1,2,3,4)
 *    total number of subsets = nC0 + nC1 + nC2 + nC3
 *
 *    using the combination recurrence ( choosing r elements at a time from a set of n elements)
 *    n	   n-1        n-1
 *     C  =    C     +   C
 *      r       r-1       r
 *
 *    we can calculate total number of subsets
 */

int subset_util(int *A, int n , int r) {

    int cnt;
    if(r>n || n<1)
	return 0;

    if(n > 0 && r == 0)
	return 1;
    if(r == n)
	return 1;

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





	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
