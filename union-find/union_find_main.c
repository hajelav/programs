/*************************************************************************************
CONCEPTS
https://www.youtube.com/watch?v=0jNmHPfA_yE
https://www.youtube.com/watch?v=VHRhJWacxis
**************************************************************************************/
#include "union_find.h"
#include "../utils.h"


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
