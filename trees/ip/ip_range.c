#include "../../utils.h"

/*
 * to store the ip range, we convert ip address into integers and store them as interval tree.
 * ip rangle overlap can easily be detected using search function in an interval tree
 */
typedef struct INTVL {
    char *ip_low;
    char *ip_high;
    uint32_t low;
    uint32_t high;
    uint32_t max;
    struct INTVL *left;
    struct INTVL *right;
} INTVL;

//global root of an interval tree
INTVL * root = NULL;

/*
 *convert an ip address into an integer
 *http://www.bennadel.com/blog/1830-converting-ip-addresses-to-and-from-integer-values-with-coldfusion.htm
 */
uint32_t convert_ip_to_int(char *ip) {
    /*this function assumes that the ip address a valid*/
    char *token;
    uint32_t _ip = 0, i = 3;

    //get the first token
    token = strtok(ip, ".");

    //walk through the tokens
    while(token!=NULL){
	/*printf("%s\n", token);*/

	//shift the token 24 bits, then 16 bits then 8 bits then 0 bits and keep ORing
	_ip |= atoi(token) << (8*i);
	token = strtok(NULL, ".");
	i--;
    }
    return _ip;
}

INTVL* create_interval_node(char *ip_low, char *ip_high, uint32_t low, uint32_t high) {

    INTVL *temp;

    if(!ip_low || !ip_high)
	return NULL;

    temp = (INTVL*)malloc(sizeof(INTVL));
    if(!temp)
	return NULL;

    temp->ip_low = ip_low;
    temp->ip_high = ip_high;
    temp->low = low;
    temp->high = high;
    temp->max = high; //set the max as high when you create a node
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

/*return 1 if intervals overlap, else return 0*/
int is_interval_overlap(INTVL *intvl1, uint32_t low, uint32_t high){

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
    printf("[%s  %s] Max:%u\n", intvl->ip_low, intvl->ip_high, intvl->max);
    print_interval_tree(intvl->right);
}

void create_interval_tree(INTVL *intvl, char *ip_low, char *ip_high, uint32_t low, uint32_t high) {

    INTVL *temp;

    if(!intvl)
	return;


    if(low <= intvl->low) {
	if(!intvl->left){
	    temp = create_interval_node(ip_low, ip_high, low, high);
	    intvl->left = temp;
	} else
	    create_interval_tree(intvl->left, ip_low, ip_high, low, high);
    } else {
	if(!intvl->right) {
	    temp = create_interval_node(ip_low, ip_high, low, high);
	    intvl->right = temp;
	} else 
	    create_interval_tree(intvl->right, ip_low, ip_high, low, high);
    }

    /*
     *update the max value at each node
     *  max at each node = MAX (high value of node, max value of left node, max value of right node)
     */
    intvl->max = MAX_three(intvl->high, intvl->left?intvl->left->max:INT_MIN, intvl->right?intvl->right->max:INT_MIN);
}


/*search for a given interval in an interval tree. If an interval is found we return the pointer to that node, otherwise return NULL*/
INTVL* interval_search(INTVL *intvl, uint32_t low, uint32_t high) {

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

int main() {

    char c;
    INTVL *result;
    int choice;
    char ip_low[16];
    char ip_high[16];
    uint32_t low = 0, high = 0;

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- Insert ip address interval into Interval tree\n");
	printf("2 -- Print\n");
	printf("3 -- search for interval in an interval tree\n");
	
	printf("enter your choice\n");
	scanf("%d", &choice);

	switch(choice) {

	    case 1: 
		printf("Enter ip low\n");
		scanf("%s", ip_low);
		printf("Enter ip high\n");
		scanf("%s", ip_high);
 		low = convert_ip_to_int(ip_low);
		high = convert_ip_to_int(ip_high);

		if(!root){
		root = create_interval_node(ip_low, ip_high, low, high);
		} else {
		 create_interval_tree(root, ip_low, ip_high, low, high);
		}
		break;
	    case 2: 
		print_interval_tree(root);
		break;

	    case 3:
		printf("Enter interval low\n");
		scanf("%u", &low);
		printf("Enter interval high\n");
		scanf("%u", &high);
		result = interval_search(root, low, high);
		if(result)
		printf("Overlapping interval to [%u  %u] : [%u  %u]\n", low, high, result->low, result->high);
		else 
		printf("Overlapping interval to [%u  %u] : NULL\n", low, high);
		break;


	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');
    return 0;
}
