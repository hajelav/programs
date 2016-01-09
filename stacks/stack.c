#include "../utils.h"
#define STACK_SIZE 32

typedef struct _stack {
    int top;
    char *arr;
} STACK;

STACK* init_stack() {

    STACK *s;
    s = (STACK*)malloc(sizeof(STACK));

    if(!s)
	return NULL;

    s->top = -1; //initialize the top
    s->arr = (char*)calloc(STACK_SIZE, sizeof(char));

    if(!s->arr)
	return NULL;

    return s;
}

void push(STACK *s, char elem) {

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
	printf("%c ", s->arr[i]);
    }

    printf("\n");
}

/*
 * LinkedIn question
 *Given a nested list of integers, returns the sum of all integers in the list weighted by their depth 
 *For example, given the list {1,1},2,{1,1}} the function should return 10 (four 1's at depth 2, one 2 at depth 1) 
 *Given the list {1,{4,{6}}} the function should return 27 (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3) 
 */

int weighted_depth_sum(char *str) {

    STACK *s = NULL;
    int sum = 0;

    /*initialze the stack*/
    s = init_stack();

    while(*str) {

	/*if we get a { } combination, then pop the stack*/
	if(s->arr[s->top] == '{' && *str == '}')
	    pop(s);
	//if we get a number then calculate the weighted sum
	else if(*str-'0' >= 0 && *str-'0' <= 9)
	    sum += (s->top+1)*(*str-'0'); 

	else if(*str!= ','){
	    push(s, *str);
	}
	
	str++;
    }

    return sum;
}

int main() {
    /*char c;*/
    int choice;
    char S[128];
    /*do {*/

    printf("MENU OPTIONS\n");
    printf("1 -- weighted sum of nested integers\n");

    printf("\n");
    printf("Enter your choice\n");
    scanf("%d",&choice);
    switch(choice){

	case 1:
	    printf("enter nested integer string, Eg {{1,1},2,{1,1}}\n");
	    scanf("%s", S);
	    printf("weighted sum : %d\n", weighted_depth_sum(S));
	    break;

	default:
	    printf("Invalid option\n");
	    break;
    }
    printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}

