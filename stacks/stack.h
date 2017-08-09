#include "../utils.h"
#define STACK_SIZE 32

typedef struct _stack {
    int top;
    char *arr;
} STACK;

STACK* init_stack();
void push(STACK *s, char elem);
void pop(STACK *s);
int isEmpty(STACK *s);
void print_stack(STACK *s);
void free_stack(STACK *s);
