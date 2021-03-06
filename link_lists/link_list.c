/* link lists */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*defining the link list structure*/

typedef struct LIST {
    int value;
    struct LIST *random;
    struct LIST *next;
} LIST;

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

/*reverse link list recursively*/

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


/*
 *remove n th Node From End of List
 *Given a linked list, remove the n-th node from the end of list and return its head.
 *
 *Example:
 *
 *Given linked list: 1->2->3->4->5, and n = 2.
 *
 *After removing the second node from the end, the linked list becomes 1->2->3->5.
 *
 */

LIST* removeNthFromEnd(LIST* head, int n) {

    LIST *nextNode, *prevNode, *tempNode;

    if(!head || (n<=0))
        return NULL;

    /*initialize two pointers pointing to head*/
    nextNode = head;
    prevNode = head;


    /*since we are doing it in single pass, we move the nextNode n positons forward*/
    while(n > 0 && nextNode){
        nextNode = nextNode->next;
        n--;
    }

    /*
     *if we happen to reach to the end of list, that means, we need to delete the first element
     *    of the node. Therefore we make the head point to the next element of the list
     */
    if(!nextNode){
        head = prevNode->next;
        prevNode->next = NULL;
        free(prevNode);
        return head;
    }

    /*
     *run both prev and next pointers, after the while loop ends, prevNode will point to 
     *    the previous element to be deleted
     */

    while(nextNode && nextNode->next) {
        prevNode = prevNode->next;
        nextNode = nextNode->next;
    }


    /*remove the node*/
    tempNode = prevNode->next;

    if(tempNode) {
        prevNode->next = tempNode->next;
        tempNode->next = NULL;
        free(tempNode);

    } else {
        /*
         *if tempNode is NULL, that means there is only one element in the list , so
         *    head points to null
         */
        head = tempNode;
    }

    return head;

}

/*
 *rotate list
 *Given a linked list, rotate the list to the right by k places, where k is non-negative.
 *
 *Example 1:
 *
 *Input: 1->2->3->4->5->NULL, k = 2
 *Output: 4->5->1->2->3->NULL
 *Explanation:
 *rotate 1 steps to the right: 5->1->2->3->4->NULL
 *rotate 2 steps to the right: 4->5->1->2->3->NULL
 *Example 2:
 *
 *Input: 0->1->2->NULL, k = 4
 *Output: 2->0->1->NULL
 *Explanation:
 *rotate 1 steps to the right: 2->0->1->NULL
 *rotate 2 steps to the right: 1->2->0->NULL
 *rotate 3 steps to the right: 0->1->2->NULL
 *rotate 4 steps to the right: 2->0->1->NULL
 */


LIST* rotateRight(LIST* head, int k) {

    int listLen = 0, rotateCount, rotatePivot, count = 1;
    LIST *trav, *newList, *newHead;
    if(!head)
        return NULL;

    /*get the len of the list*/
    trav = head;
    while(trav){
        listLen++;
        trav = trav->next;
    }

    /*
     *move to the point where the list needs to be rotated
     *    after the while loop ends , trav will point to the 
     *    node from where we need to rotate the list
     */
    rotateCount = k % listLen;
    rotatePivot = listLen - rotateCount;

    trav = head;
    while(count < rotatePivot){
        trav = trav->next;
        count++;
    }

    if(trav->next){

        /*newList is the start of the newList, which is the newHead*/
        newList = trav->next;
        newHead = newList;

        /*move to the end of the newList*/
        while(newList->next)
            newList = newList->next;

        /*seperate the list after the rotatePivot */
        trav->next = NULL;

        /*join the old head to the newList*/
        newList->next = head;
    } else {
        /*
         *if the next node to the rotation point is NULL, then we dont need to
         *rotate the list
         */
        newHead = head;
    }

    return newHead;
}


/*
 *plus one linked list
 *
 *Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.
 *
 *You may assume the integer do not contain any leading zero, except the number 0 itself.
 *
 *The digits are stored such that the most significant digit is at the head of the list.
 *
 *Example:
 *Input:
 *1->2->3
 *
 *Output:
 *1->2->4
 *
 */

LIST* plusOne(LIST* head) {

    LIST *list, *tempList;
    LIST *newList = NULL;

    int S, C = 0;

    if(!head)
        return NULL;

    /*reverse the list first to add 1 to LSB*/
    list = reverse_list(head);

    /*add 1 to LSB first*/
    S = (list->value + 1 + C)%10;
    C = (list->value + 1 + C)/10;

    /*insert the sum , into a newly created list*/
    newList = insert_item(newList, S);

    tempList = list->next;

    /*loop though remainder of the list, and add sum to the newList*/
    while(tempList) {

        S = (tempList->value + C)%10;
        newList = insert_item(newList, S);
        C = (tempList->value + C)/10;

        tempList = tempList->next;

    }

    /*after running through the whole list, if C > 0, add the carry to the newList*/
    if(C>0){
        newList = insert_item(newList, C);
    }

    //print_list(newList);
    return newList;
}


/*
 *
 *convert sorted singly link list to binary search tree
 *
 *Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
 *
 *For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
 *
 *Example:
 *
 *Given the sorted linked list: [-10,-3,0,5,9],
 *
 *One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 *
 *            0
 *           / \
 *         -3   9
 *         /   /
 *       -10  5
 */

/*Definition for singly-linked list.*/
struct ListNode {
    int val;
    struct ListNode *next;
};
/*Definition for a binary tree node.*/
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createTreeNode(int val) {

    struct TreeNode *treeNode;
    treeNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    if(!treeNode)
        return NULL;
    treeNode->left = NULL;
    treeNode->right = NULL;
    treeNode->val = val;

    return treeNode;

}

/*get the middle node*/
struct ListNode* getMiddleNode(struct ListNode *node){

    struct ListNode *slowNode, *fastNode;
    if(!node)
        return NULL;

    slowNode = node;
    fastNode = node;

    /*run two pointers, one twice fast than the other*/
    while(fastNode && fastNode->next){
        slowNode = slowNode->next;
        fastNode = fastNode->next->next;
    }

    return slowNode;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {


    struct ListNode *midNode, *leftList, *rightList;
    struct TreeNode *treeNode; 

    if(!head)
        return NULL;

    /*get the middle node of the list*/
    midNode = getMiddleNode(head);

    /*the right list is the list next to the the midNode*/
    rightList = midNode->next;

    /*
     *if the list has only one node, ie the midNode is same as head
     *then set leftList to NULL
     */
    if(midNode->val == head->val)
        leftList = NULL;
    else
        /*the leftList start node will be head*/
        leftList = head;

    /*
     *seperate the list by the mid point, ie go the the previous node of
     *midNode, and set its next to NULL
     */
    while(head->next) { 
        if(head->next->val == midNode->val)
            break;

        head = head->next;
    }
    head->next = NULL;

    /*create a treeNode with the value of midNode*/
    treeNode = createTreeNode(midNode->val);

    treeNode->left = sortedListToBST(leftList);
    treeNode->right = sortedListToBST(rightList);

    return treeNode;

}

/*
 *
 *merge two sorted lists
 *Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
 *
 *Example:
 *
 *Input: 1->2->4, 1->3->4
 *Output: 1->1->2->3->4->4
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
            new = insert_item(new, h1->value);
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

/*
 *swap nodes in pairs
 *Given a linked list, swap every two adjacent nodes and return its head.
 *
 *Example:
 *
 *Given 1->2->3->4, you should return the list as 2->1->4->3.
 *Note:
 *
 *Your algorithm should use only constant extra space.
 *You may not modify the values in the list's nodes, only nodes itself may be changed.
 */

LIST* swapPairs(LIST* head) {

    LIST *temp, *currNode, *nextNode, *newHead = NULL, *prevNode;

    if(!head)
        return NULL;

    prevNode = NULL;
    currNode = head;
    nextNode = currNode->next;


    /*if there is only one node, just return the head*/
    if(!nextNode)
        return head;

    while(currNode && nextNode){

        /*store the pointer to the next node of nextNode*/
        temp = nextNode->next;

        /*store the second node of the list as head*/
        if(!newHead)
            newHead = nextNode;

        /*interchange the pair of currNode and nextNode*/
        nextNode->next = currNode;
        currNode->next = temp;


        if(prevNode)
            prevNode->next = nextNode;

        /*store the previous node(to be used in next iteration)*/
        prevNode = currNode;

        /*move the currNode to the next pair*/
        currNode = temp;

        /*move the nextNode to the next pair, if currNode is not NULL*/
        if(currNode)
            nextNode = currNode->next;

    }

    /*return the newHead, ie second node of the original list*/
    return newHead;

}

/*
 *remove duplicates from sorted list
 *
 *Given a sorted linked list, delete all duplicates such that each element appear only once.
 *
 *Example 1:
 *
 *Input: 1->1->2
 *Output: 1->2
 *Example 2:
 *
 *Input: 1->1->2->3->3
 *Output: 1->2->3
 */

LIST* deleteDuplicates(LIST *head){

    LIST *currNode, *nextNode;

    if(!head)
        return NULL;

    currNode = head;
    nextNode = head->next;

    while(currNode && nextNode) {

        if(currNode->value == nextNode->value){
            /*duplicate exists. delete it*/
            currNode->next = nextNode->next;
            nextNode->next = NULL;
            free(nextNode);

            /*make nextNode to the next node in the list*/
            nextNode = currNode->next;
        } else {
            currNode = currNode->next;
            nextNode = nextNode->next;
        }
    }

    return head;
}

/*
 *delete node in a linked list, given the access to only that node
 *Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
 *
 *Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.
 *
 */

void deleteNode(LIST* node) {

    LIST *temp;
    if(!node || (!node->next))
        return;

    node->value = node->next->value;
    temp = node->next;
    node->next = node->next->next;
    temp->next = NULL;
    free(temp);
}


/*
 *reverse linked list iteratively
 *Reverse a singly linked list.
 *
 *Example:
 *
 *Input: 1->2->3->4->5->NULL
 *Output: 5->4->3->2->1->NULL
 */

LIST* reverseList(LIST *node ) {

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

/*
 *function to detect a loop/cycle in a link list
 */
bool detectLoop(LIST* node) {

    LIST *currNode, *nextNode;

    if(!node)
        return false;

    currNode = nextNode = node;

    while(nextNode && nextNode->next){

        currNode = currNode->next;
        nextNode = nextNode->next->next;

        if(currNode == nextNode)
            return true;
    }
    return false;
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


/*linked list cycle - return the node where the cycle begins*/

LIST* hasCycle(LIST *node) {

    LIST *currNode, *nextNode;

    if(!node)
        return NULL;

    currNode = nextNode = node;

    while(nextNode && nextNode->next){

        currNode = currNode->next;
        nextNode = nextNode->next->next;

        if(currNode == nextNode)
            return currNode;
    }

    return NULL;

}


LIST *detectCycle(LIST *head) {

    LIST *node, *nodeInCycle;
    int cycleLen = 1;
    if(!head)
        return NULL;

    /*find if there exists in cycle*/
    nodeInCycle = hasCycle(head);

    if(!nodeInCycle)
        return NULL;

    /*find the length of the cycle */
    node = nodeInCycle;
    while(node->next != nodeInCycle){
        node = node->next;
        cycleLen++;
    }


    /*move the node pointer to the length of the cycle(cycleLen)*/
    node = head;
    while(cycleLen-1 > 0){
        node = node->next;
        cycleLen--;
    }


    /*
     *run the node pointer and head simultaneously, 
     *the next of node pointer and head meet at the cycle start node
     */
    while(node->next != head){
        node = node->next;
        head = head->next;
    }

    /*
     *to remove cycle, we need to do
     *    node->next = NULL
     */


    /*head is the node where the cycle starts*/
    return head; 
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
 *add two numbers represented by link list
 You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

 You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 Example

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
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

    l1 = list1;
    l2 = list2;

    while(l1 && l2){
        S = (l1->value + l2->value + C)%10;
        C = (l1->value + l2->value +C)/10;	

        newsum = insert_item(newsum, S);
        l1 = l1->next;
        l2 = l2->next;
    }

    //if any of the two list is non empty
    if(l1 || l2) {
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

    }

    if(C > 0){
        //insert the node for the last carry if its > 0
        newsum = insert_item(newsum, C);
    }

    newsum = reverse_list(newsum);
    return newsum;
}

/*
 *remove linked list elements
 *Remove all elements from a linked list of integers that have value val.
 *
 *Example:
 *
 *Input:  1->2->6->3->4->5->6, val = 6
 *Output: 1->2->3->4->5
 */

LIST* removeElements(LIST *head, int val) {

    LIST *currNode, *temp;

    if(!head)
        return NULL;

    currNode = head;

    while(currNode && currNode->next){

        if(currNode->next->value == val){
            temp = currNode->next;
            currNode->next = temp->next;
            temp->next = NULL;
            free(temp);
        } else {
            currNode = currNode->next;
        }

    }

    /*if head has same value as val, then delete it and move the head forward*/
    if(head->value == val){
        temp = head;
        head = head->next;
        temp->next = NULL;
        free(temp);
    }
    return head;
}


/*
 *intersection of two linked lists
 *
 *Write a program to find the node at which the intersection of two singly linked lists begins.
 *
 *
 *For example, the following two linked lists:
 *
 *A:          a1 → a2
 *                   ↘
 *                    c1 → c2 → c3
 *                   ↗            
 *B:     b1 → b2 → b3
 *begin to intersect at node c1.
 *
 *Notes:
 *
 *If the two linked lists have no intersection at all, return null.
 *The linked lists must retain their original structure after the function returns.
 *You may assume there are no cycles anywhere in the entire linked structure.
 *Your code should preferably run in O(n) time and use only O(1) memory.
 */

LIST* getIntersectionNode(LIST *headA, LIST *headB) {

    int lenHeadA = 0, lenHeadB = 0, len, count = 0;
    LIST *trav = NULL, *first, *second;

    /*get length of the first list*/
    trav = headA;
    while(trav){
        lenHeadA++;
        trav = trav->next;
    }

    /*get length of the second list*/
    trav = headB;
    while(trav){
        lenHeadB++;
        trav = trav->next;
    }

    /*find the absolute diff in len for the lists*/
    len = (lenHeadA - lenHeadB) > 0 ? lenHeadA - lenHeadB : lenHeadB - lenHeadA;

    if(lenHeadA - lenHeadB > 0){

        /*first list is longer, so move the pointer 'len' distance forward*/
        first = headA;
        while(count < len){
            first = first->next;
            count++;
        }
        /*second points to start of the second list*/
        second = headB;

    } else {

        /*second list is longer, so move the pointer 'len' distance forward*/
        second = headB;
        while(count < len){
            second = second->next;
            count++;
        }
        /*first points to start of the first list*/
        first = headA;

    }

    /*
     *move both first and second pointer, whereever the pointers meet, thats
     *the intersection of the lists
     */

    while(first && second){

        if(first == second)
            return first;
        first = first->next;
        second = second->next;

    }

    /*the lists do not intersect, so return NULL*/
    return NULL;
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
 *Move last element to front of a given Linked List
 */
LIST* moveLastElemToFront(LIST* node) {

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
        printf("b-Sort the list\t");
        printf("c-Delete alternate nodes\t");
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
                deleteDuplicates(head);
                print_list(head);
                break;
            case '8':
                printf("Enter the node to  be deleted\n");
                scanf("%d",&n1);
                head = removeElements(head, n1);
                print_list(head);
                break;
            case '9':
                if(!(head = reverseList(head)))
                    printf("List is empty");
                else
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
                print_list(swapPairs(head));
                break;

            case 'l':
                sort_linklist(head);
                break;

            case 'm':
                printf("Enter nth node\n");
                scanf("%d", &n);
                removeNthFromEnd(head, n);
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
