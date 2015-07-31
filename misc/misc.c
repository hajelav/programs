
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

int main(){


    char c;
    int choice;
    double num;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Square root of a number\n");
	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter number\n");
		scanf("%lf", &num);
		printf("Square root:%lf\n", sqroot(0, num, num));
		break;

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
