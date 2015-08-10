
/* link lists */

#include <stdio.h>
#include <stdlib.h>

/*defining the link list structure*/

typedef struct DLIST {
    int value;
    struct DLIST* next;
    struct DLIST* prev;

} DLIST;

DLIST* create_node (int value) {
    DLIST *temp = (DLIST*)malloc(sizeof(DLIST));
    temp->next = NULL;
    temp->prev = NULL;
    temp->value = value;
    return temp;
}
/* inserts items into the doubly link list */
DLIST*  insert_item(DLIST* node,int value) {
    DLIST *temp;

    temp = create_node(value);
    if(node == NULL){
	node = temp;
    }
    else {
	temp->next= node;
	node->prev = temp;
	node = temp; 
    }
    return node;
}
/*prints the list*/
void print_list(DLIST* head){
    DLIST* trav = head;
    if(trav == NULL)
	printf("List is empty\n");
    while(trav!=NULL){
	printf("%d-->",trav->value);
	trav=trav->next;
    }
    printf("NULL");
    printf("\n");
}

/*find an item in the list*/
DLIST* find_item (DLIST* head,int value) {
    DLIST * trav = head;
    if(trav->value == value){
	return trav;
    }else{
	while(trav->next!=NULL){
	    if(trav->next->value == value)
		return trav;
	    trav=trav->next;
	}

    }
    return NULL;
}

/* delete an item from the list */
DLIST* delete_item(DLIST* head,int value) {
    DLIST *trav,*temp;
    trav = find_item(head,value);
    if(trav){ 
	if (trav == head ){
	    head = trav->next;
	    trav->next = NULL;
	    free(trav);
	}else{
	    temp = trav->next->next;
	    trav->next->next = NULL;
	    free(trav->next);
	    trav->next = temp;
	}
	printf("Item deleted successfully\n");
    }else
	printf("Item not found\n");

    return head;

}
/*reverse the link list  by reversing the pointers*/
DLIST* reverse_list(DLIST *node){
    DLIST *temp;
    if(node == NULL)
	return node;
    temp = reverse_list(node->next);
    if(temp==NULL)
	temp=node;
    else{
	node->next->next = node;
	node->next = NULL;
    }
    return temp; 
}

/*reverse the link list recursively */
DLIST * reverse ( DLIST* node ) {
    static DLIST* temp;
    static DLIST * head;

    if(node == NULL)
	return NULL;

    else {
	reverse(node->next);
	if(temp == NULL){
	    head = node;
	    temp = head;
	}else {
	    temp->next = node;
	    node->next = NULL;
	    temp=node;
	}
    }
    return head;
}

/*remove the duplicate nodes from sorted link list */
void delDuplicateFromSortedLL(DLIST *head){

    DLIST* ptr1, *ptr2;

    if(head == NULL)
	return;

    ptr1 = head;
    ptr2 = head->next;

    while(ptr1 && ptr2) {

	if(ptr2->value == ptr1->value){
	    //duplicate exists. delete it
	    ptr1->next = ptr2->next;
	    free(ptr2);
	    //make ptr2 the next node in the list
	    ptr2 = ptr1->next;
	} else {
	    ptr1 =  ptr1->next;
	    ptr2 = ptr2->next;
	}
    }
}


/*
 *merge two sorted link list
 */

DLIST* merge_list(DLIST* head1, DLIST* head2){

    DLIST *h1, *h2, *new;
    DLIST *trav;
    h1=head1;
    h2=head2;
    new = NULL;


    if(h1==NULL && h2==NULL)
	return NULL;
    else if(h1==NULL && h2!=NULL)
	return h2;
    else if (h1!=NULL && h2==NULL)
	return h1;

    while(h1 && h2){
	if(h1->value < h2->value){
	    new = insert_item(new, h1->value);
	    h1 = h1->next;
	}else if (h1->value > h2->value){
	    new = insert_item(new, h2->value);
	    h2 = h2->next;
	} else {
	    new = insert_item(new, h2->value);
	    h1 = h1->next;
	    h2 = h2->next;
	}
    }

    trav = h1?h1:h2;
    while(trav){

	new = insert_item(new, trav->value);
	trav = trav->next;
    }
    return new;
}

void print_inorder(DLIST *root) {
    if(root == NULL)
	return;
    print_inorder(root->prev);
    printf("%d ", root->value);
    print_inorder(root->next);

}

DLIST* get_middle(DLIST* node, DLIST** left, DLIST** right) {

    DLIST *slow, *fast, *temp;

    if(!node)
	return node;

    slow = node;
    fast = node;

    while(fast && fast->next!=NULL) {
	slow = slow->next;
	fast = fast->next->next;
    }

    temp = slow->prev;
    while(temp && temp->prev) {
	temp = temp->prev;
    }

    *left = temp;
    *right = slow->next;

    //seperate the mid element form the mid element
    if(slow->next) {
    slow->next->prev = NULL;
    slow->next = NULL;
    }
    if(slow->prev){
	slow->prev->next = NULL;
	slow->prev = NULL;
    }
    return slow;
}

DLIST* convert_DLL_to_bin_tree(DLIST *node) {

    DLIST *mid, *left = NULL, *right = NULL;
    if(!node)
	return NULL;

    /*get the middle of the list and fill the left and right pointers*/
    mid = get_middle(node, &left, &right);

    if(node == mid)
	return node;

    mid->prev = convert_DLL_to_bin_tree(left);
    mid->next = convert_DLL_to_bin_tree(right);

    return mid;
}

int main() {
    int choice, item;
    DLIST *head, *root;
    head=NULL;

    char c;
    do  {
	//scanf("%c",&c);
	printf("MENU OPTIONS\n");
	printf("1--insert\n");
	printf("2--print\n");
	printf("3--convert linklist to binary tree(in place)\n");
	printf("q--quit\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter the item to be added\n");
		scanf("%d",&item);
		head = insert_item(head,item);
		break;
	    case 2:
		print_list(head);
		break;
	    case 3:
		root = convert_DLL_to_bin_tree(head);
		print_inorder(root);
		break;
	    default:
		printf("Invalid option\n");
		break;
	}
    }while((c=getchar())!='q');
    return 0;
}
