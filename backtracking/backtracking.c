/*
 *Backtracking 
 *http://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../utils.h"


#define STACK_SIZE 32

typedef struct _stack {
    int top;
    int *arr;
} STACK;

STACK* init_stack() {

    STACK *s;
    s = (STACK*)malloc(sizeof(STACK));

    if(!s)
	return NULL;

    s->top = -1; //initialize the top
    s->arr = (int*)calloc(STACK_SIZE, sizeof(int));

    if(!s->arr)
	return NULL;

    return s;
}

void push(STACK *s, int elem) {

    if(s->top == STACK_SIZE){
	printf("stack full\n");
	return;
    }
    s->arr[++s->top] = elem;
}

void pop(STACK *s) {

    if(!s)
	return;

    s->arr[s->top] = '\0';
    s->top--;
}

int isEmpty(STACK *s){

    if(s && s->top == -1)
	return 1;
    return 0;
}

void print_stack(STACK *s) {

    int i;

    if(!s)
	return;

    for(i=0;i<STACK_SIZE;i++){
	if(s->arr[i])
	    printf("%d ", s->arr[i]);
    }
    printf("\n");
}

void free_stack(STACK *s) {

    if(s){
	free(s->arr);
	s->arr = NULL;
	free(s);
    }
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

/*
 *permutations of a string
 Time Complexity: O(n*n!)
 */
void string_permutation(char *str, int l, int h) {

    int i;
    if(l==h)
	printf("%s\n", str);

    // for all chars in the string
    for(i=l;i<h;i++){

	swap_str(str, l, i);
	string_permutation(str, l+1, h);
	swap_str(str, l, i);
    }
}


/*
 *leetcode problem 39
 *Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
 *
 *The same repeated number may be chosen from C unlimited number of times.
 *
 *Note:
 *All numbers (including target) will be positive integers.
 *Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
 *The solution set must not contain duplicate combinations.
 *For example, given candidate set 2,3,6,7 and target 7, 
 *    A solution set is: 
 *    [7] 
 *    [2, 2, 3] 
 */

void combination_sum(int *A, int i, int len, STACK *S, int sum){

    int j;

    if(sum == 0){
	print_stack(S);
	return;
    }

    for(j=i;j<len;j++){

	if(A[j] <= sum){
	    push(S, A[j]);
	    combination_sum(A, i, len, S, sum-A[j]);
	    pop(S);
	}
    }
}

int main() {
    char c;
    int choice, n, sum;
    STACK *S = NULL;
    char *str;
    int *A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- All permutations of a string(backtracking)\n");
	printf("2 -- N Queen problem\n");
	printf("3 -- combination sum problem\n");


	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter length of string\n");
		scanf("%d", &n);
		str = create_string(n);
		input_string(str);
		printf("Permutations\n");
		string_permutation(str, 0, n);
		break;

	    case 2:
		printf("Enter board length(NXN))\n");
		scanf("%d", &n);
		break;

	    case 3:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);

		printf("enter sum\n");
		    scanf("%d", &sum);

		S = init_stack();
		combination_sum(A, 0, n, S, sum);
		

		break;

	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
