#include "../../utils.h"

/*
 *interval tree data stucture : used to do operations on interval.
 *apart from storing the interval low and high value, we als store max which is the max value of any interval end point rooted at a given node
 */
typedef struct INTVL {
 int low;
 int high;
 int max;
 struct INTVL *left;
 struct INTVL *right;
} INTVL;

//global root of an interval tree
INTVL * root = NULL;

INTVL* create_interval_node(int low, int high) {

    INTVL *temp;
    temp = (INTVL*)malloc(sizeof(INTVL));
    if(!temp)
	return NULL;
    temp->low = low;
    temp->high = high;
    temp->max = high; //set the max as high when you create a node
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

/*return 1 if intervals overlap, else return 0*/
int is_interval_overlap(INTVL *intvl1, int low, int high){

    if(!intvl1 || (low == high))
	return 0;

    if((intvl1->high < low) || (high < intvl1->low))
	return 0;
    else 
	return 1;
}

void print_interval_tree(INTVL *intvl) {

    if(!intvl)
	return;

    print_interval_tree(intvl->left);
    printf("[%d  %d] Max:%d\n", intvl->low, intvl->high, intvl->max);
    print_interval_tree(intvl->right);
}

void create_interval_tree(INTVL * intvl, int low, int high) {

    INTVL *temp;

    if(!intvl)
	return;

    if(low <= intvl->low) {
	if(!intvl->left){
	    temp = create_interval_node(low, high);
	    intvl->left = temp;
	} else
	    create_interval_tree(intvl->left, low, high);
    } else {
	if(!intvl->right) {
	    temp = create_interval_node(low, high);
	    intvl->right = temp;
	} else 
	    create_interval_tree(intvl->right, low, high);
    }

    /*update the max value at each node*/
    intvl->max = MAX_three(intvl->high, intvl->left?intvl->left->max:INT_MIN, intvl->right?intvl->right->max:INT_MIN);
}

int main() {

    char c;
    int choice;
    int low, high;

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- Insert interval into Interval tree\n");
	printf("2 -- Print\n");
	
	printf("enter your choice\n");
	scanf("%d", &choice);

	switch(choice) {

	    case 1: 
		printf("Enter interval low\n");
		scanf("%d", &low);
		printf("Enter interval high\n");
		scanf("%d", &high);

		if(!root){
		root = create_interval_node(low, high);
		} else {
		 create_interval_tree(root, low, high);
		}
		break;
	    case 2: 
		print_interval_tree(root);
		break;


	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');

    return 0;
}
