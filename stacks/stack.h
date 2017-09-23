#include "../utils.h"

typedef struct _stack {
    int top;
    char *arr;
    int size;
} STACK;

STACK* init_stack(int size);
void push(STACK *s, char elem);
void pop(STACK *s);
int isEmpty(STACK *s);
void print_stack(STACK *s);
void print_stack1(STACK *s);
void free_stack(STACK *s);
char get_top_element(STACK *s);


