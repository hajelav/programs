/* link lists */

#include <stdio.h>
#include <stdlib.h>

/*defining the link list structure*/

typedef struct LIST {
    int value;
    struct LIST *random;
    struct LIST *next;
} LIST;

typedef struct DLIST {
    int val;
    struct LIST* next;
    struct LIST* prev;

} DLIST;

LIST* create_node (int value) {
    LIST *temp = (LIST*)malloc(sizeof(LIST));
    temp->next = NULL;
    temp->random = NULL;
    temp->value = value;
    return temp;
}
/* inserts items into the link list */
LIST*  insert_item(LIST* node,int value) {
    LIST *temp;

    temp = create_node(value);
    if(node == NULL){
        node = temp;
    }
    else {
        temp->next= node;
        node = temp; 
    }
    return node;
}
/*prints the list*/
void print_list(LIST* head){
    LIST* trav = head;
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
LIST* find_item (LIST* head,int value) {
    LIST * trav = head;
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
LIST* delete_item(LIST* head,int value) {
    LIST *trav,*temp;
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
LIST* reverse_list(LIST *node){
    LIST *temp;
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

/*reverse the link list iteratively */

LIST * reverse_iter (LIST *node ) {

    LIST *prev,*curr,*next;

    if (!node)
        return NULL;

    prev = NULL; //initialize prev node to NULL
    curr = node;

    while(curr!=NULL){

        /*store the next node in the list*/
        next = curr->next;

        /*reverse the pointers of the current node, so that it points to the previous node*/
        curr->next = prev;

        /*shift the prev node so that it becomes the current node*/
        prev = curr;

        /*shift the current node, so that it becomes the next node*/
        curr = next;
    }

    /*
     *at the end of the loop, the previous pointer will point to the last node of the list
     *and all the pointers would have been reversed
     */
    return prev;
}

/*reverse the link list recursively */
LIST * reverse ( LIST* node ) {
    static LIST* temp;
    static LIST * head;

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

/* pair wise swap of elements */

/*LIST* pairwise_swap(LIST* node){
  LIST* trav,first,second;
  trav = node;
  if (trav = NULL)
  return NULL;
  first = trav;
  second = trav->next;


  }*/
/*remove the duplicate nodes from sorted link list */
void delDuplicateFromSortedLL(LIST *head){

    LIST* ptr1, *ptr2;

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

/* remove the duplicates from unsorted link list */

void delDuplicateFromUnsortedLL(LIST* head){

}

/*
 *merge two sorted link list
 */

LIST* merge_list(LIST* head1, LIST* head2){

    LIST *h1, *h2, *new;
    LIST *trav;
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

/*Delete all occurences of a given node */

LIST* del_all_occurence(LIST* head, int value) {

    LIST *p2,*temp,*p1;
    if(head == NULL)
        return NULL;

    p2 = head;
    /*p3 = p1->next;*/

    while(p2!=NULL) {
        if(p2->value == value){
            temp = p1->next;
            p1->next = temp->next;
            p2 = temp->next;
            free(temp);

        }else{
            p1 = p1->next;
            p2 = p2->next;
        }
    }//while ends

    //Now check for the head node
    if(head->value == value){
        temp = head;
        head = head->next;
        free(temp);
    }

    return head;
}//function ends


/*delete all occurrence of a given value in a link list(non-recursive)*/
LIST* delete_all_occurences_nonrecursive(LIST* node, int value) {

    LIST *curr_node = NULL, *next_node = NULL;
    LIST *temp;
    if(!node)
        return NULL;

    curr_node = NULL; //set current pointer to null
    next_node = node; // set next pointer to head node

    while(next_node){

        if(next_node->value == value){

            if(!curr_node){
                /*the head node matches the value, so we need to delete it*/
                temp = next_node->next;
                next_node->next = NULL;
                free(next_node);
                next_node = temp;

                /*point the head node to the next node, and current still points to NULL*/
                node = next_node;

            } else {
                curr_node->next = next_node->next;
                next_node->next = NULL;
                free(next_node);
                next_node = curr_node->next;

            }
        } else {
            curr_node = next_node;
            next_node = next_node->next;
        }
    }
    return node;
}

/*delete all occurrence of a given value in a link list(recursive)*/
void delete_all_occurences_recursive(LIST** node, int value) {

    LIST *temp;

    if(node && (*node)->next == NULL)
        return;
    if(!node)
        return;

    delete_all_occurences_recursive(&(*node)->next, value);
    temp = (*node)->next;
    if(temp) {
        if(temp->value == value){
            (*node)->next = temp->next;
            free(temp);
        }
    }
}


/*Pair waise swap of link list (just the value)*/

int pair_wise_swap (LIST *node) {


    int temp;
    while (node != NULL && node->next!=NULL) {
        temp = node->next->value;
        node->next->value = node->value;
        node->value = temp;
        node = node->next->next;
    }
    return 1;

}

/*
 *pair wise swap by changing the links
 */

LIST* pair_wise_swap_links(LIST* node){


    LIST *prev = NULL, *cur, *next;
    LIST *head;

    if(!node)
        return NULL;

    head = node;
    cur = node;
    next = node->next;

    while(cur && next) {
        cur->next = next->next;
        next->next = cur;
        if(!prev){
            head = next;
        } else {
            prev->next = next;
        }

        prev = cur;
        cur = cur->next;
        if(cur)
            next = cur->next;
    }

    return head;
} 
/*
 *pair wise swap recursive
 *leetcode problem 24
https://leetcode.com/problems/swap-nodes-in-pairs/
*/

void pair_wise_swap_recur (LIST *node) {
    int temp;
    if((node == NULL) || (node->next == NULL)) 
        return;

    temp = node->next->value;
    node->next->value = node->value;
    node->value = temp;
    pair_wise_swap_recur(node->next->next);	
    /*return;*/
}

/*Sorting of linklist using bubble sort */
void sort_list ( LIST *head) {
    int count=0,tmp,i;
    LIST *node;
    node=head;
    /*count the number of elements*/
    while (node!=NULL){
        count++;
        node=node->next;
    }
    /*do a bubble sort */
    for ( i=1;i<count;i++){
        node = head;
        while(node->next!=NULL){
            if(node->value > node->next->value)
            {
                tmp = node->value;
                node->value = node->next->value;
                node->next->value = tmp;
            }
            node = node->next;
        }
    }
}

/* method 1: delete alternate nodes */
void delete_alternate ( LIST* node ) {
    LIST *temp;
    while ( node!=NULL && node->next!= NULL) {
        temp = node->next;
        node->next = node->next->next;
        free(temp);

        node = node->next;
    }
}

/* method 2 : delete alternate nodes */

void deleteAlternateNodes(LIST* node) {

    LIST *ptr1, *ptr2;

    ptr1 = node;
    if(!ptr1)
        return;
    ptr2 = node->next;

    while(ptr1 && ptr2){

        ptr1->next = ptr2->next;
        free(ptr2);
        //adjust the pointers
        ptr1 = ptr1->next;
        if(ptr1)
            ptr2 = ptr1->next;
    }
}
/* function to print the middle element of a link list */
LIST* get_middle(LIST *node){

    LIST *ptr1, *ptr2;
    if(node == NULL)
        return NULL;
    if(!node->next)
        return node;

    ptr1 = ptr2 = node;

    while(ptr2 && ptr2->next!=NULL){

        ptr1=ptr1->next;
        ptr2=ptr2->next->next;
    }

    return ptr1;

}

/* function to delete a link-list using recursion */

void  delLinkList(LIST*node, LIST** temp){
    if(node == NULL)
        return;

    delLinkList(node->next, temp);
    if(*temp == NULL){
        *temp = node;
    } else {
        free(*temp);
        node->next = NULL;
        *temp = node;
    }

}

/*
 *function to detect a loop/cycle in a link list
 */
int detectLoop(LIST* node){
    LIST* ptr1, *ptr2;

    ptr1 = ptr2 = node;

    while(ptr2 && ptr2->next && ptr1!=ptr2){

        if(ptr1 == ptr2)
            return 1;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next->next;
    }

    return 0;
}


/*
 *detect and remove loop from linklist
 *http://www.geeksforgeeks.org/detect-and-remove-loop-in-a-linked-list/
logic :
This method is also dependent on Floyd’s Cycle detection algorithm.
1) Detect Loop using the detect loop function above and get the pointer to a loop node.
2) Count the number of nodes in loop. Let the count be k.
3) Fix one pointer to the head and another to kth node from head.
4) Move both pointers at the same pace, they will meet at loop starting node.
5) Get pointer to the last node of loop and make next of it as NULL.
*/


/* Function to remove loop.
 *  loop_node --> Pointer to one of the loop nodes
 *   head -->  Pointer to the start node of the linked list */
void removeLoop(LIST *loop_node, LIST *head)
{
    LIST *ptr1 = loop_node;
    LIST *ptr2 = loop_node;

    // Count the number of nodes in loop
    unsigned int k = 1, i;
    while (ptr1->next != ptr2)
    {
        ptr1 = ptr1->next;
        k++;
    }

    // Fix one pointer to head
    ptr1 = head;

    // And the other pointer to k nodes after head
    ptr2 = head;
    for (i = 0; i < k; i++)
        ptr2 = ptr2->next;

    /*  Move both pointers at the same pace,
        they will meet at loop starting node */
    while (ptr2 != ptr1)
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    // Get pointer to the last node
    ptr2 = ptr2->next;
    while (ptr2->next != ptr1)
        ptr2 = ptr2->next;

    /* Set the next node of the loop ending node
       to fix the loop */
    ptr2->next = NULL;
}
/* This function detects and removes loop in the list
 *   If loop was there in the list then it returns 1,
 *     otherwise returns 0 */
int detectAndRemoveLoop(LIST *list)
{
    LIST  *slow_p = list, *fast_p = list;

    while (slow_p && fast_p && fast_p->next)
    {
        slow_p = slow_p->next;
        fast_p  = fast_p->next->next;

        /* If slow_p and fast_p meet at some point then there
         *            is a loop */
        if (slow_p == fast_p)
        {
            removeLoop(slow_p, list);

            /* Return 1 to indicate that loop is found */
            return 1;
        }
    }

    /* Return 0 to indeciate that ther is no loop*/
    return 0;
}


/*
 *Clone a linked list with next and random pointer
 */

LIST* cloneLinkList(LIST* olist) {

    LIST* temp, *head, *old, *new, *newhead;
    head = olist;
    if(olist == NULL)
        return NULL;

    /*  pass 1: insert a node in front of each node of original list  */
    while(olist){

        temp = create_node(olist->value);
        /*temp->value = olist->value;*/

        temp->next = olist->next;
        olist->next = temp;

        olist = temp->next;
    }

    /* pass 2 : link the random pointers */

    olist = head;
    while(olist){

        olist->next->random = olist->random->next;
        olist = olist->next->next; 

    }

    /* pass 3 : seperate original and new list */

    old = head;
    newhead = old->next;
    new = newhead;

    while(old){

        old->next = old->next->next;
        old = old->next;

        if(new->next){
            new->next = new->next->next;
            new = new->next;

        }
    }

    return newhead;
}

/*
 *Move last element to front of a given Linked List
 */
LIST* moveLastElemToFront(LIST* node){

    LIST* ptr1, *ptr2, *head;

    if(node== NULL)
        return NULL;
    //store the head 
    head = node;
    ptr1 = node;
    ptr2 = node->next;
    while(ptr2 && ptr2->next){

        ptr2 = ptr2->next;
        ptr1 = ptr1->next;
    }

    //set the second last node's next to NULL
    if(ptr2) {
        ptr1->next = NULL;
        //set the last node's next to head , so that it becomes the new head
        ptr2->next = head;
        head = ptr2;
    } 

    return head;
}

/*
 *add two numbers represented by link list
 */

LIST* addNumbers(LIST* list1, LIST* list2){

    LIST *l1, *l2;
    int S, C = 0;
    LIST *newsum = NULL;
    LIST *trav;

    if(!list1 && !list2)
        return NULL;
    else if(!list1 && list2)
        return list2;
    else if(!list2 && list1) 
        return list1;

    l1 = reverse_list(list1);
    l2 = reverse_list(list2);

    while(l1 && l2){
        S = (l1->value + l2->value + C)%10;
        C = (l1->value + l2->value)/10;	

        newsum = insert_item(newsum, S);
        l1 = l1->next;
        l2 = l2->next;
    }

    //check which of the list is smaller, the one which is not NULL will obviously be bigger

    trav = l1?l1:l2;
    if(trav) { //atleast one list is longer

        while(trav) {
            S = (trav->value + C)%10;
            C = (trav->value + C)/10;
            newsum = insert_item(newsum, S);
            trav = trav->next;
        }
    } 
    if(C > 0){
        //insert the node for the last carry if its > 0
        newsum = insert_item(newsum, C);
    }

    /*newsum = reverse_list(newsum);*/
    return newsum;
}

/*
 *Delete nodes which have a greater value on right side
http://www.geeksforgeeks.org/delete-nodes-which-have-a-greater-value-on-right-side/
*/

LIST* delNodesGreaterRight(LIST* node) {
    LIST *ptr1, *ptr2, *head = NULL;

    if(!node)
        return NULL;

    node = reverse_list(node);

    ptr1 = node;
    ptr2 = node->next;

    while(ptr1 && ptr2){
        if(ptr1->value > ptr2->value){
            ptr1->next = ptr2->next;
            free(ptr2);
        }
        //save the head pointer
        if(!head){
            head = ptr1;
        }
        ptr1 = ptr1->next;
        if(ptr1)
            ptr2 = ptr1->next;
    }
    return(reverse_list(head));
}

/*
 *Segregate even and odd nodes in a Linked List
 Given a Linked List of integers, write a function to modify the linked list such that all even numbers appear before all the odd numbers in the modified linked list. Also, keep the order of even and odd numbers same.
 */

LIST* segEvenOddNodes(LIST* node){

    LIST *head, *ptr1 = NULL, *ptr2, *temp;
    //ptr1 = always points to the tail of the even list so that we keep on adding new nodes
    //as we traverse the original list.

    if(!node)
        return NULL;

    head = node;
    if(node->value%2 == 0){
        ptr1 = node;
    } 


    ptr2 = node;
    while(ptr2 && ptr2->next){

        if(ptr2->next->value%2 == 0){
            if(ptr1 == NULL){
                ptr1 = ptr2->next;
                ptr2->next = ptr1->next;
                ptr1->next = head;
                head = ptr1;
            }else {
                temp = ptr2->next;
                ptr2->next = ptr2->next->next;

                temp->next = ptr1->next;
                ptr1->next = temp;
                ptr1 = ptr1->next;

            }
        }  else {// if the element found is not even, move the ptr2 pointer
            ptr2 = ptr2->next;
        }
    }
    return head;
}


/*
 *XOR Linked List – A Memory Efficient Doubly Linked List 
 *http://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-1/
 *http://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-2/
 */

/*
 *Given a linked list of line segments, remove middle points
 *http://www.geeksforgeeks.org/given-linked-list-line-segments-remove-middle-points/
 */


/* mergesort on link list */
void sort_linklist(LIST *node) {

}

/*
 *leetcode problem 19
 *https://leetcode.com/problems/remove-nth-node-from-end-of-list/
solution: do using single pass only
*/

void remove_nth_node_from_last_util(LIST *head, int  *cnt, int n) {

    LIST *temp;
    if(!head || n<=0)
        return;

    remove_nth_node_from_last_util(head->next, cnt, n);

    (*cnt)++;
    if(*cnt == n+1){
        temp = head->next;
        if(temp){
            head->next = temp->next;
            free(temp);
        }
    }
}

void remove_nth_node_from_last(LIST *head, int n) {

    int count = 0;
    LIST *temp;
    if(!head || n<=0)
        return;

    remove_nth_node_from_last_util(head, &count, n); 

    //if n happen to be the first node, then delete it here
    if(count == n){

        temp = head;
        head = head->next;
        free(temp); 
    }
    print_list(head);
}

int main() {
    int item,n,n1,n2,list1[50],list2[50];
    LIST *head1=NULL;
    LIST *head2=NULL;
    LIST *head, *temp = NULL;

    int i;
    LIST* head3;
    head=NULL;

    char c;
    while(1) {
        //scanf("%c",&c);
        printf("MENU OPTIONS\t");
        printf("1--insert\t");
        printf("2--print\t");
        printf("3--find\t");
        printf("4--delete\t");
        printf("5--reverse recursively\t");
        printf("6--Merge\n");
        printf("7--Delete duplicate\t");
        printf("8--Delete all occerences of a given value\t");
        printf("9--reverse iteratively\t");
        printf("a-Pair wise swap\t");
        printf("b-Sort the list\t");
        printf("c-Delete alternate nodes\t");
        printf("d--Write a function to print the middle of a given linked list\t");
        printf("e--delete a link list using recursion\t");
        printf("f--clone a link list with random pointer\t");
        printf("g--Move last element to front of a given Linked List\t");
        printf("h--add two numbers represented by link lists\t");
        printf("i--Delete nodes which have a greater value on right side\t");
        printf("j--Segregate even and odd nodes in a Linked List\t");
        printf("k--pair wise swap links\t");
        printf("l--sort the list(efficient way:Mergesort)\t");
        printf("m--Remove Nth Node From End of List)\t");
        printf("q--quit\n");
        printf("Enter your choice\n");
        scanf("%c",&c);
        switch(c){
            case '1':
                printf("Enter the item to be added\n");
                scanf("%d",&item);
                head = insert_item(head,item);
                break;
            case '2':
                print_list(head);
                break;
            case '3':
                printf("Enter the item to be searched\n");
                scanf("%d",&item);
                if(head!=NULL){
                    if(find_item(head,item) == NULL)
                        printf("Item not found\n");
                    else
                        printf("Item found\n");
                }else
                    printf("List is empty\n");
                break;
            case '4':
                printf("Enter the element to be deleted\n");
                scanf("%d",&item);
                if(head!=NULL)
                    head=delete_item(head,item);
                else
                    printf("List is empty\n");
                break;
            case '5':

                if(!(head = reverse_list(head)))
                    /*if(!(head = reverse(head)))*/
                    printf("List is empty");
                print_list(head);
                break;
            case '6':
                printf("Enter the no of  elements in list1\n");
                scanf("%d",&n1);
                for(i=0;i<n1;i++){
                    scanf("%d",&list1[i]);
                    head1=insert_item(head1,list1[i]);
                }
                printf("Enter the no of  elements in list2\n");
                scanf("%d",&n2);
                for(i=0;i<n2;i++){
                    scanf("%d",&list2[i]);
                    head2=insert_item(head2,list2[i]);
                }

                printf("\nFirst list\n");
                print_list(head1);
                printf("\nSecond list\n");
                print_list(head2);
                printf("\nMerged list\n");
                head3 = merge_list(head1,head2);
                print_list(head3);
                break;
            case '7':
                delDuplicateFromSortedLL(head);
                print_list(head);
                break;
            case '8':
                printf("Enter the node to  be deleted\n");
                scanf("%d",&n1);
                /*head = del_all_occurence(head,n1);*/
                head = delete_all_occurences_nonrecursive(head, n1);
                /*delete_all_occurences_recursive(&head, n1);*/
                print_list(head);
                break;
            case '9':
                if(!(head = reverse_iter(head)))
                    printf("List is empty");
                else
                    print_list(head);

                break;

            case 'a':
                // if(pair_wise_swap(head))
                pair_wise_swap_recur(head);
                print_list(head);
                break;
            case 'b':
                sort_list(head);
                print_list(head);
                break;
            case 'c':
                /*delete_alternate(head);*/
                deleteAlternateNodes(head);
                print_list(head);
                break;
            case 'd':
                temp = get_middle(head);
                printf("Middle element: %d\n", temp?temp->value:0);
                break;

            case 'e':
                delLinkList(head, &temp);
                print_list(head);
                break;
            case 'f':
                cloneLinkList(head);
                print_list(head);
                break;

            case 'g':
                head = moveLastElemToFront(head);
                print_list(head);
                break;

            case 'h':
                printf("Enter the no of  elements in list1\n");
                scanf("%d",&n1);
                for(i=0;i<n1;i++){
                    scanf("%d",&n);
                    head1=insert_item(head1,n);
                }
                printf("Enter the no of  elements in list2\n");
                scanf("%d",&n2);
                for(i=0;i<n2;i++){
                    scanf("%d",&n);
                    head2=insert_item(head2,n);
                }

                printf("\nFirst list\n");
                print_list(head1);
                printf("\nSecond list\n");
                print_list(head2);
                printf("\nSum link list\n");
                head3 = addNumbers(head1,head2);
                print_list(head3);
                break;

            case 'i':
                print_list(delNodesGreaterRight(head));
                break;

            case 'j':
                print_list(segEvenOddNodes(head));
                break;
            case 'k':
                print_list(pair_wise_swap_links(head));
                break;

            case 'l':
                sort_linklist(head);
                break;

            case 'm':
                printf("Enter nth node\n");
                scanf("%d", &n);
                remove_nth_node_from_last(head, n);
                break;

            case 'q':
                exit(0);
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    }
    return 0;
}