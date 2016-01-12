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

/*inorder printing of interval tree*/
void print_interval_tree(INTVL *intvl) {

    if(!intvl)
	return;

    print_interval_tree(intvl->left);
    printf("[%d  %d] Max:%d\n", intvl->low, intvl->high, intvl->max);
    print_interval_tree(intvl->right);
}

void create_interval_tree(INTVL *intvl, int low, int high) {

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

    /*
     *update the max value at each node
     *  max at each node = MAX (high value of node, max value of left node, max value of right node)
     */
    intvl->max = MAX_three(intvl->high, intvl->left?intvl->left->max:INT_MIN, intvl->right?intvl->right->max:INT_MIN);
}


/*search for a given interval in an interval tree. If an interval is found we return the pointer to that node, otherwise return NULL*/
INTVL* interval_search(INTVL *intvl, int low, int high) {

    INTVL *result;

    if(!intvl)
	return NULL;

    if(is_interval_overlap(intvl, low, high))
	return intvl;

    if(intvl->left && intvl->left->max >= low)
	result = interval_search(intvl->left, low, high);
    else 
	result = interval_search(intvl->right, low, high);

    return result;
}


void merge_interval(INTVL *intvl, int low, int high) {

    /*case 1: interval->high lies between low and high*/

    if((low <= intvl->high) && (intvl->high <= high)) {
	intvl->high = high;
    }

    /*case 2: interval->low lies between low and high*/
    if((low <= intvl->low) && (intvl->low <= high)) {
	intvl->low = low;
    }

    /*update the max in the interval node*/
    intvl->max = intvl->high;
}

/*
 * http:www.geeksforgeeks.org/given-n-appointments-find-conflicting-appointments/
 * Given n appointments, find all conflicting appointments
 *
 * this can be solved using interval tree. add the first appt slot to interval tree. From second appt onwards
 * keep on adding appt slots into the interval tree and detect overlap while adding. This can be done in O(log(n)) time. 
 */

int main() {

    char c;
    INTVL *result;
    int choice;
    int low, high;

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- Insert interval into Interval tree\n");
	printf("2 -- Print\n");
	printf("3 -- search for interval in an interval tree\n");
	printf("4 -- find the coverage of set of intervals\n");
	
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

	    case 3:
		printf("Enter interval low\n");
		scanf("%d", &low);
		printf("Enter interval high\n");
		scanf("%d", &high);
		result = interval_search(root, low, high);
		if(result)
		printf("Overlapping interval to [%d  %d] : [%d  %d]\n", low, high, result->low, result->high);
		else 
		printf("Overlapping interval to [%d  %d] : NULL\n", low, high);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');
    return 0;
}
