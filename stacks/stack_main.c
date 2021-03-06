#include "stack.h"
#include "../utils.h"
#define STACK_SIZE 32

/*
concept for stock prices questions
https://www.youtube.com/watch?v=g1USSZVWDsY
*/

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
    s = init_stack(STACK_SIZE);

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

    free_stack(s);

    return sum;
}

int reverse_polish_notation_value(char *str){

    /*this function assumes that the input is valid postfix string without brackets*/

    STACK *s = NULL;
    int sum = 0;
    int op1 = 0, op2 = 0;

    /*initialze the stack*/
    s = init_stack(STACK_SIZE);

    while(*str) {

	/*if we encounter a number, we push into the stack*/
	if(*str-'0' >= 0 && *str-'0' <= 9)
	    push(s, *str);
	else {

	    /*check if there is atleast two operators present in stack*/
	    if(s->top < 1){
		printf("Not a valid postfix expression\n");
		return INT_MIN;
	    }

	    switch(*str){

		//get operand 1 from stack
		op1 = s->arr[s->top];
		s->arr[s->top] = 0;
		pop(s);
		//get operand 2 from stack
		op2 = s->arr[s->top];
		s->arr[s->top] = 0;
		pop(s);

		case '-':
		push(s, op1-op2);
		break;
		case '+':
		push(s, op1+op2);
		break;
		case '/':
		push(s, op1/op2);
		break;
		case '*':
		push(s, op1*op2);
		break;

	    }//switch ends
	}
	str++;
    }

    /*the final expression value will be stored in stack*/
    sum = s->arr[s->top];
    free_stack(s);
    
    return sum;
}

/*http://www.geeksforgeeks.org/expression-evaluation*/
int  infix_evaluation(char *infix) {

    return 0;
}

int main() {
    /*char c;*/
    int choice;
    char S[128];
    /*do {*/

    printf("MENU OPTIONS\n");
    printf("1 -- weighted sum of nested integers\n");
    printf("2 -- evaluate the value of an expression given in reverse polish notation(postfix)\n");
    printf("3 -- infix expression evaluation\n");



    printf("\n");
    printf("Enter your choice\n");
    scanf("%d",&choice);
    switch(choice){

	case 1:
	    printf("enter nested integer string, Eg {{1,1},2,{1,1}}\n");
	    scanf("%s", S);
	    printf("weighted sum : %d\n", weighted_depth_sum(S));
	    break;

	case 2:
	    printf("enter the expression in reverse polish notation Eg {{1,1},2,{1,1}}\n");
	    scanf("%s", S);
	    printf("value : %d\n", reverse_polish_notation_value(S));


	default:
	    printf("Invalid option\n");
	    break;
    }
    printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}
