#include "stack.h"

STACK* init_stack(size) {

    STACK *s;
    s = (STACK*)malloc(sizeof(STACK));

    if(!s)
	return NULL;

    s->top = -1; //initialize the top
    s->arr = (char*)calloc(size, sizeof(char));
    s->size = size;

    if(!s->arr)
	return NULL;

    return s;
}

void push(STACK *s, char elem) {

    if(s->top == s->size){
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

void print_stack1(STACK *s) {

    int i;

    if(!s)
	return;

    for(i=0;i<s->size;i++){
	printf("%c ", s->arr[i]);
    }
    printf("\n");
}
void print_stack(STACK *s) {

    if(!s)
	return;
    printf("%s\n", s->arr);
}

void free_stack(STACK *s) {

    if(s){
	free(s->arr);
	s->arr = NULL;
	free(s);
    }
}



