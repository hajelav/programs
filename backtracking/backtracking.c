/*
 *Backtracking 
 *http://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*function pointer of min/max heapify functions*/


int* create_1Darray(int n) {
    int *A;
    A = (int*)calloc(n, sizeof(int));

    if(!A)
	return NULL;
    return A;
}

void input_array(int *A, int n) {
    int i;
    printf("Enter elements\n");
    for(i=0;i<n;i++){
	scanf("%d", &A[i]);
    } 
}

void print_1Darray(int *A, int n) {
    int i;
    for(i=0;i<n;i++){
	printf("%d ", A[i]);
    } 
}

void print_1Darray_index(int *A, int i, int j){
int k;
    for(k=i;k<=j;k++){
	printf("%d ", A[k]);
    } 
    printf("\n");
}

void swap(char *A, int idx1, int idx2) {
    int temp;
   temp = A[idx1];
   A[idx1] = A[idx2];
   A[idx2] = temp;
}

int MAX(int *A, int a, int b) {
    return A[a]>A[b]?a:b;
}
int MIN(int *A, int a, int b) {
    return A[a]>A[b]?b:a;
}

char * create_string(int len){
    char *str;
    str = (char*)malloc(sizeof(char)*(len+1));
    str[len] = '\0';
    return str;
}

void input_string(char *str) {
    printf("Enter string\n");
    scanf("%s", str);
}

void string_permut(char *str, int l, int h) {

    int i;
    if(l==h)
	printf("%s\n", str);

    // for all chars in the string
    for(i=l;i<h;i++){

	swap(str, l, i);
	string_permut(str, l+1, h);
	swap(str, l, i);

    }

}

int main() {
    char c;
    int choice, n;
    char *str;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- All permutations of a string(backtracking)\n");
	printf("2 -- N Queen problem)\n");

	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter length of string\n");
		scanf("%d", &n);
		str = create_string(n);
		input_string(str);
		printf("Permutations\n");
		string_permut(str, 0, n);
		break;

	    case 2:
		printf("Enter board length(NXN))\n");
		scanf("%d", &n);
		break;
	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
