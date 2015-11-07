#include "utils.h"

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

int MOD(int x, int y) {
    return (x-y)>0?(x-y):(0-(x-y));
}

int MIN_three(int a, int b, int c) {

    if(a-b <= 0 && a-c <=0)
	return a;
    else if(b-a <= 0 && b-c <= 0 )
	return b;
    else 
	return c;
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

/*create an array of integer pointer*/

int** create_1D_array_ptr(int n) {

    int **A;
    A = (int**)calloc(n, sizeof(int*));
    if(!A)
	return NULL;
    return A;
}

void input_array(int *A, int n) {

    if(!A)
	return;
    int i;
    for(i=0;i<n;i++){
	scanf("%d", &A[i]);
    }
}

void init_2Darray(int **A, int r, int c, int val) {
    int i, j;
    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    A[i][j] = val;
	}
    }
}

void init_2Dchar_array(char **A, int r, int c, char val) {

    int i, j;
    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    A[i][j] = val;
	}
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

char ** create_2Dchar_array(int r, int c) {

    int i;
    char **A = (char**)malloc(sizeof(char*)*r);
    for(i=0;i<r;i++){
	A[i] = (char*)calloc(c+1, sizeof(char));
    }
    return A;
}


char* create_1Dchar_array(int n) {
    char* temp;
    temp = (char*)calloc(sizeof(char), n+1);
    temp[n] = '\0';
    return temp?temp:NULL;
}

int** create_2Darray(int xlen, int ylen) {
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


void print_2Darray(int **t, int xlen, int ylen) {

    int i, j;
    for(i=0;i<xlen;i++){
	for(j=0;j<ylen;j++){
	    printf("%d  ",t[i][j]);
	}
	printf("\n");
    }
}

void input_2Darray(int **A, int r, int c) {

    int i, j;
    printf("Enter elements\n");
    for(i=0;i<r;i++){
	for(j=0;j<c;j++){
	    scanf("%d",&A[i][j]);
	}
    }
}
void input_2Dchar_array(char**A, int r, int c) {

    int i;
    printf("Enter elements\n");
    for(i=0;i<r;i++){
	    scanf("%s", A[i]);
    }
}

void input_1Darray(int *A, int n) {

    int i;
    for(i=0;i<n;i++){
	scanf("%d", &A[i]);
    }
}
void print_2Dchar_array(char **T, int xlen, int ylen) {

    int i, j;
    for(i=0;i<xlen;i++){
	for(j=0;j<ylen;j++){
	    if(T[i][j])
	    printf("%c ",T[i][j]);
	}
	printf("\n");
    }
}

void print_1Darray(int *A, int n) {
    int i;
    for(i=0;i<n;i++){
	printf("%d ", A[i]);
    }
}
