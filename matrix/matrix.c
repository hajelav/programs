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

int ** rotate_matrix(int r, int c) {

}


int main(){


    char c;
    int choice;
    int row, col;
    int **A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Rotate matrix by 90 degree\n");
	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter no of rows\n");
		scanf("%d", &row);
		printf("Enter no of cols\n");
		scanf("%d", &col);

		A = rotate_matrix(row, col);
		print_2Dmatrix(A, col, row);
		break;

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
