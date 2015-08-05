#include <stdio.h>
#include <stdlib.h>

//define tree structure
typedef struct TREE {
    int value;
    struct TREE *left;
    struct TREE *right;
    struct TREE* successor;
    int isThreaded:1;
}TREE;

/* Augmented tree structure, used to calculate n-order statistics */
typedef struct ATREE {
    int value;
    struct ATREE *left;
    struct ATREE *right;
    struct ATREE* successor;
}ATREE;

/* data structure to implement level-order(BFS) in tree */
typedef struct L_ORDER {
    struct L_ORDER* next;
    int val;
}L_ORDER;

/* data structure to implement level-order(BFS) in tree */
typedef struct LIST {
    L_ORDER *head;
    L_ORDER *tail;
}LIST;

int MIN(int a , int b) {
    return(a<b?a:b);
}
int MAX(int a , int b) {
    return(a<b?b:a);
}

L_ORDER* create_list(int val) {
    L_ORDER *lorder;
    lorder = (L_ORDER*)malloc(sizeof(L_ORDER));
    lorder->next = NULL;
    lorder->val = val;
    return lorder;
}

int checkNodeLevel(TREE* node, int n1, int n2, int lvl) {

    static int level1, level2;
    if(node==NULL)
	return -1;

    checkNodeLevel(node->left, n1, n2, lvl+1);
    if(node->value == n1){
	level1=lvl;
    }
    if(node->value == n2){
	level2=lvl;
    }
    checkNodeLevel(node->right, n1, n2, lvl+1);

    return(level2-level1);
}

/* maximum path sum between two leaves of a binary tree
 * http://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/ 
 * logic: for a node
 * 1. calculate the left sum
 * 2. calculate the right sum
 * 3.if the sum of left + right + node value is greater than max then set it the new max
 * 4. return greater of leftSum and RightSum*/


int maxSumTwoLeaves(TREE *node, int *maxSum){

    int leftS, rightS;
    if(node == NULL)
	return -1;
    if(node->left == NULL && node->right == NULL)
	return node->value;

    leftS = node->value + maxSumTwoLeaves(node->left, maxSum);
    rightS = node->value + maxSumTwoLeaves(node->right, maxSum);

    //check for sum of left, right and node-value
    if(leftS + rightS - node->value > *maxSum)
	*maxSum = leftS + rightS - node->value;

    if(leftS >= rightS)
	return leftS;
    else 
	return rightS;

}

/* maximum sum leaf to root path in a Binary Tree */

int maxLeafToRootSum(TREE* node) {

    int leftSum, rightSum;
    if(node==NULL)
	return 0;
    if(node->left == NULL && node->right == NULL)
	return node->value;

    leftSum = node->value + maxLeafToRootSum(node->left);
    rightSum = node->value + maxLeafToRootSum(node->right);

    if(leftSum >= rightSum)
	return leftSum;
    else 
	return rightSum;
}

void swapData(TREE* nodeL, TREE* nodeR){
     int temp;
	temp = nodeL->value;
	nodeL->value = nodeR->value;
	nodeR->value = temp;
}

/* Reverse alternate levels of a perfect binary tree */

void reverseAlternateLevels(TREE *nodeL, TREE* nodeR , int level){

    if(nodeL == NULL || nodeR == NULL){
	return;
    }

    reverseAlternateLevels(nodeL->left, nodeR->right, level+1);
    if(level % 2 == 0){
	printf("%d", level);
	swapData(nodeL, nodeR);
    }
    reverseAlternateLevels(nodeL->right, nodeR->left, level+1);
}


int checkForCousins(TREE* node, int n1, int n2, int lvl, TREE* parent) {

    static int lvl_n1, lvl_n2;

    if(node == NULL) {
	return 0;
    }

    checkForCousins(node->left, n1, n2, 2*lvl+1, node);
    if(node->value == n1 ) {
	lvl_n1 = (parent->left == node) ? (lvl-1)/2 : (lvl-2)/2;
    }
    if(node->value == n2 ) {
	lvl_n2 = (parent->left == node) ? (lvl-1)/2 : (lvl-2)/2;
    }
    checkForCousins(node->right, n1, n2, 2*lvl+2, node);

    return(lvl_n2 - lvl_n1);
}

int checkCousins(TREE* node, int n1, int n2, int lvl, TREE* parent) {

    if(node == NULL || checkNodeLevel(node, n1, n2, lvl) > 0)
	return 0;

    return checkForCousins(node, n1, n2, lvl, parent);
}

/* find node in binary Tree */

TREE* findNodeInBinaryTree(TREE* node, int key) {

    TREE* ret1, *ret2;
    if(node==NULL)
	return NULL;

    if(node->value == key)
	return node;
    

    ret1 = findNodeInBinaryTree(node->left, key);
    ret2 = findNodeInBinaryTree(node->right, key);

    if(ret1)
	return ret1;
    else if(ret2)
	return ret2;
    else
	return NULL;
}
TREE* getLeftMostNode(TREE* node) {

    if (node==NULL){
	return NULL;
    }

    while(node->left!=NULL){
	node = node->left;
    }

    return node;
}
/* find inorder successor in BST(O(log(n)) solution */
int inOrderSuccInBST(TREE *node, int key){

    TREE *tnode, *temp;

    if(node==NULL) {
	return -1;
    }

    tnode = findNodeInBinaryTree(node, key);
    printf("tnode = %d\n",tnode?tnode->value:-1);
    if(tnode) {
	if(tnode->right != NULL) {
	    //if the keys right child is not null then find the left most element in the right subtree
	    temp =  getLeftMostNode(tnode->right);
	    return(temp->value);
	}  else { //if right child is NULL
	    //find the last node greater than key while traversing the path from root to key
	    int succ = -1;
	    while(node && node->value!=key){
		    
		if(node->value < key){
		    node=node->right;
		} else if(node->value > key){
		    succ = node->value;
		    node=node->left;
		}
	    }//while ends
	    return succ;
	}
    }  else {
	//key not found
	return -1;
    }
}

int inOrderPredInBST(TREE *node, int key){

    /* find the key first
     * if(key found)
     * {
     * if(left child is not NULL){
     * find the max of subtree with left child as root
     * }
     *  gelse {
     *
     *  }
     * } */

}

/* convert to threaded binary tree: 
 *  In a simple threaded binary tree, the NULL right pointers are used to store inorder successor.
 *  Where-ever a right pointer is NULL, it is used to store inorder successor. */

void convertToThreadedBinTree(TREE *node, TREE** in_prev) {

    if(node==NULL)
	return;

    convertToThreadedBinTree(node->left, in_prev);

    if(*in_prev!=NULL) {
	(*in_prev)->isThreaded = 1;
	(*in_prev)->right = node;
	*in_prev = NULL;
    }
    if(node->right == NULL){
	*in_prev = node;
    }
    convertToThreadedBinTree(node->right, in_prev);
}


void printThreadedBintree(TREE* node) {

    TREE* temp;
    if(node==NULL)
	return;
    temp = getLeftMostNode(node);

    while(temp!=NULL) {

	printf("%d-->", temp->value);
	if(temp->isThreaded){
	    temp = temp->right;
	} else {
	    temp = getLeftMostNode(temp->right);
	}
    }
}

/* add nodes to the array of list, for printing BFS */
void add_list(LIST *list, int val) {

    L_ORDER *temp;

    if(list->head == NULL) {
	list->head = create_list(val);
	list->tail = list->head;
    } else {
	temp = create_list(val);
	list->tail->next = temp;
	list->tail = list->tail->next;	
    }
}

int count_nodes(TREE* node) {
    if(node==NULL){
	return 0;
    }
    return(count_nodes(node->left) + count_nodes(node->right) + 1);
}



 void print_level_order(LIST* list, int height) {

    int i;
    for(i=0;i<height;i++) {
	while(list[i].head != NULL){
	    printf("%d ", list[i].head->val);
	    list[i].head = list[i].head->next;
	}
	printf("\n");
    }

}
/* level order traversal of a tree (BFS) */
/* logic : we do an inorder travsersal and maintain the level info
 * in a variable(lvl). Whenever we find an element at a given level we
 * add it to the link list. At the end when the recursion is over all the elements are
 * stored in the linklist. So at the end all the nodes are printed in levels */
void level_order_tree(TREE* node, int lvl, LIST* list) {

    if(node==NULL){
	return;
    }
    level_order_tree(node->left, lvl+1, list);
    add_list(&list[lvl], node->value);
    level_order_tree(node->right, lvl+1, list);


} 

/* function to check if a tree is a complete tree or not */

/* for a tree to be complete these 3 conditions should be met
 * 1. if we find any node with node->left==NULL and node->right!=NULL then tree is not complete
 * 2. for all non-leaf nodes(ie level less than the max level) , at the max we can only one node with node->left == NULL && node->right ==NULL
 *    ie if we find a node with  above property then all non-leaf nodes should have the same condition true  
 * 3. if we find any node with condition node->lett !=NULL && node->right == NULL then we should not find this condition true for any
 *    node after that*/
   
int is_binary_tree_complete(TREE *node, int lvl, int height) {

    static int boolean;
    if(node == NULL)
	return ;

    is_binary_tree_complete(node->left, lvl+1, height);
    /*for non-leaf nodes*/
    if(lvl < height) {
	/*case 1*/
	if(node->left==NULL && node->right!=NULL){
	boolean = 1;
	}
    }


}

/*
 * algo-2 to check if the binary tree is complete
 *Calculate the number of nodes (count) in the binary tree.
 *Start recursion of the binary tree from the root node of the binary tree with index (i) being set as 0 and the number of nodes in the binary (count).
 *If the current node under examination is NULL, then the tree is a complete binary tree. Return true.
 *If index (i) of the current node is greater than or equal to the number of nodes in the binary tree (count) i.e. (i>= count), then the tree is not a complete binary. Return false.
 *Recursively check the left and right sub-trees of the binary tree for same condition. For the left sub-tree use the index as (2*i + 1) while for the right sub-tree use the index as (2*i + 2).iCalculate the number of nodes (count) in the binary tree.
 *Start recursion of the binary tree from the root node of the binary tree with index (i) being set as 0 and the number of nodes in the binary (count).
 *If the current node under examination is NULL, then the tree is a complete binary tree. Return true.
 *If index (i) of the current node is greater than or equal to the number of nodes in the binary tree (count) i.e. (i>= count), then the tree is not a complete binary. Return false.
 *Recursively check the left and right sub-trees of the binary tree for same condition. For the left sub-tree use the index as (2*i + 1) while for the right sub-tree use the index as (2*i + 2).
 *
 */

int isBinaryTreeComplete(TREE* node, int idx, int tot_num_of_nodes) {

    int l1, l2;
    if(node == NULL){
	return 1;
    }

    if(idx>=tot_num_of_nodes){
	return 0;
    }

    l1 = isBinaryTreeComplete(node->left, 2i+1, tot_num_of_nodes);
    l2 = isBinaryTreeComplete(node->right, 2i+2, tot_num_of_nodes);

    return(l1 && l2);
}

/*
 *Remove nodes on root to leaf paths of length < K
 *Given a Binary Tree and a number k, remove all nodes that lie only on root to leaf path(s) of length smaller than k. If a node X lies on multiple root-to-leaf paths and if any of the paths has path length >= k, then X is not deleted from Binary Tree. In other words a node is deleted if all paths going through it have lengths smaller than k.
 *
 */

void removeNodesOnLeafPaths(TREE* node, int lvl, TREE* parent, int k) {

    if(node == NULL){
	return;
    }
    removeNodesOnLeafPaths(node->left, lvl+1, node, k);
    removeNodesOnLeafPaths(node->right, lvl+1, node, k);
    if(parent && node->left == NULL && node->right == NULL && lvl < k) {
	if(parent->right == node){
	    printf("deleing node %d\n", node->value);
	    free(node);
	    parent->right = NULL;
	} else {
	    printf("deleing node %d\n", node->value);
	    free(node);
	    parent->left = NULL;
	}
    } else if (parent ==NULL && node->left == NULL && node->right == NULL && lvl < k){
	free(node);
    }

}



/*Find the closest leaf in a Binary Tree*/

int closestLeafFromKey(TREE* node, int key) {

    static int key_found;
    static TREE* keyNode;
    int h1,h2;

    if(node == NULL)
	return 0;
    /* find the node with the key first */
    if(key_found == 0) {
	keyNode = findNodeInBinaryTree(node, key);
	key_found = 1;
    }


}

/*Find sum of all left leaves in a given Binary Tree*/

int countLeftLeafSum(TREE *node, TREE* parent) {

    if(node==NULL){
	return 0;
    }

    if(node->left == NULL &&
	    node->right == NULL &&
	    parent &&
	    parent->left == node) {
	return node->value;
    }

    return(countLeftLeafSum(node->left, node) + countLeftLeafSum(node->right, node));
}


/* function to find kth order statistic */

int Kth_order_stats_usingInoder(TREE* node, int order) {

    static int count,count1;
    if(node == NULL)
	return;
    Kth_order_stats_usingInoder(node->left, order);
    count++;
    if(count == order){
	count1 = node->value;
    }
    Kth_order_stats_usingInoder(node->right, order);
return count1;
}

/* remove all half nodes: nodes having just one child */

TREE* removeHalfNodes(TREE *node, TREE *parent) {

    static TREE* root;
    TREE *temp;

    if(node == NULL) {
	return NULL;
    }

    removeHalfNodes(node->left, node);
    removeHalfNodes(node->right, node);

    if(node->left!=NULL && node->right == NULL) {
	if(parent == NULL){
	    root = node->left;
	    node->left = NULL;
	    free(node);
	    return root;
	} else {
	    if(parent->right == node){
		temp = node;
		parent->right = node->left;
		temp->left = NULL;
		free(temp);
	    }
	    if(parent->left == node){
		temp = node;
		parent->left = node->left;
		temp->left = NULL;
		free(temp);
	    }
	}

    } else if(node->right!=NULL && node->left == NULL) {

	if(parent == NULL){
	    root = node->right;
	    node->right = NULL;
	    free(node);
	    return root;
	} else {
	    if(parent->right == node){
		temp = node;
		parent->right = node->right;
		temp->right = NULL;
		free(temp);
	    }
	    if(parent->left == node){
		temp = node;
		parent->left = node->right;
		temp->right = NULL;
		free(temp);
	    }

	}
    }

    return node;
}


TREE *root = NULL;
// create node

TREE *create_node() {
    TREE *node;
    node = (TREE *)malloc(sizeof(TREE));
    node->value = 0;
    node->isThreaded = 0;
    node->left = NULL;
    node->right = NULL;
    node->successor = NULL;
}
/*find : recursive*/

TREE *find_node(TREE* node, int value) {
    if(node==NULL)
	return NULL;
    if((node->left == NULL) && (node->right == NULL)){
	return node;
    }
    if(value <= node->value){
	if(node->left!=NULL)
	    find_node(node->left,value);
	else
	    return node;
    }
    else
	if(node->right!=NULL)
	    find_node(node->right,value);
	else 
	    return node;
}
/*find iterative*/

TREE * find_node_iter ( TREE*node , int value) {

    /*not tested*/
    if ( node == NULL)
	return NULL;

    if(node->value == value)
	return node;

    while(node->left || node->right) {

	if(node->left->value == value ||
		node->right->value == value)
	    break;

	if(value < node->value)
	    node = node->left;
	else 
	    node=node->right;

    }

    return node; 
}
//insertion
void  insert_node(TREE* node,int value) {
    TREE *temp;
    if(node == NULL){
	root = create_node();
	root->value = value;
    }
    else {
	temp = find_node(node,value);
	if(temp){
	    if(value <= temp->value){
		temp->left = create_node();
		temp->left->value = value;
	    }
	    else{
		temp->right = create_node();
		temp->right->value = value;
	    }
	}
    }
}
//delete

void delete_node (TREE *node,int value) {

    TREE *temp;
    if((temp = find_node(node,value))!=NULL){
	//when node to be delted is a leaf  node
	if(temp->left == NULL && temp->right == NULL){

	    if(temp->left->value == value){
		free(temp->left);
		temp->left == NULL;
	    }
	    else{
		free(temp->right);
		temp->right == NULL;
	    }
	}

    }
    else
	printf("Node not found\n");
    //when only left or right child is NULL
    //when node is an internal node

}

//draw binary tree
/*void draw_tree*/
//print inorder
void print_inorder(TREE* node){
    if(node == NULL)
	return;
    print_inorder(node->left);
    //printf("%d ",node->value);
    if(node->successor == NULL)
	printf("%d-->",node->value);
    else
	printf("%d-->%d\n",node->value,node->successor->value);
    print_inorder(node->right);
}
/* function to print the inorder successor of a given node in BST 
   variation of reverse inorder traversal*/

int  printSuccessorInBinTree(TREE* node,int value){
    static int temp;
    static int succ ;
    if(node == NULL)
	return;
    printSuccessorInBinTree(node->right,value);
    if(node->value == value)
	succ = temp;	 

    temp  = node->value;

    printSuccessorInBinTree(node->left,value);
    return succ;
}
//minimum
void find_minimum(TREE* node) {
    while(node!=NULL){
	if(node->left == NULL)
	    break;
	node = node->left;
    }
    printf("Min value : %d\n",node->value);
}
//maximum
TREE* find_maximum(TREE* node) {
    while(node!=NULL){
	if(node->right == NULL)
	    break;
	node = node->right;
    }
    return node;
}
//convert BST into a sorted singly link list

void  bst_to_s_lnklist(TREE *node , TREE **head){
    if (node ==  NULL)
	return;
    bst_to_s_lnklist(node->right,head);
    node->right = *head;
    if(*(head))
	(*head)->left = node;
    *head = node;
    bst_to_s_lnklist(node->left,head);
}

//print tree according to the levels
// note :this is a pseudo code : for each node ,this function stores th
// value of the left and right child in a link list

/*  TREE* print_tree_in_levels(TREE *root) {
    TREE *node;
    int value;
    LIST * trav, *head, *tail;
    node = root;
    head = create_node();
    trav = head;
    tail = trav;

    while(trav !=NULL){
    if(trav == head){
    head->value = node->value;
    value = head->value;
    }

    node = find_node(root,value);
    if(node->left!=NULL){   
    trav->next = create_node();
    trav->next->value = node->left->value;
    trav = trav->next;
    }
    if(node->right!=NULL){
    trav->next = create_node();
    trav->next->value = node->left->value;
    trav = trav->next;

    }

    tail = tail->next;
    value = tail->value;
    }




    }*/

/* function to check if the tree is a BST
   variation of reverse inorder traversal */

int is_bst(TREE* node){
    static int succ;
    static int boolean;

    if(node==NULL)
	return 0;

    is_bst(node->right);
    if(succ == 0)
	succ = node->value;
    else {
	if(succ < node->value)
	    boolean = 1;
	succ = node->value;
    }
    is_bst(node->left);

    return boolean;

}

/* to find the lowest common ancestor in a binary tree */

TREE* lowCommAncesinBinTree(TREE* node, int key1, int key2){

    TREE *ltree, *rtree;
    if(node == NULL)
	return NULL;

    if(node->value == key1 ||
	    node->value == key2){
	return node;
    }

    ltree = lowCommAncesinBinTree(node->left, key1, key2);
    rtree = lowCommAncesinBinTree(node->right, key1, key2);

    if(ltree && rtree){
	return node;
    } 
    if(ltree!=NULL && rtree == NULL){
	return ltree;
    } else if(rtree!=NULL && ltree == NULL) {
	return rtree;
    } else
	return NULL;
}

void distOfNodeFromAkey(TREE *node, int level, int *dist, int key) {

    if(node == NULL){
	return;
    }

    distOfNodeFromAkey(node->left, level+1, dist, key);
    if(node->value == key){
	*dist = level;
    }
    distOfNodeFromAkey(node->right, level+1, dist, key);

}

/* distance between two keys of a given binary tree 
 * logic : find the lowest common ancestor and then sum up the distance of keys from the
 * LCA*/


int distBetweenKeys(TREE* node, int k1, int k2){

    TREE* lca;
    int dist_k1 =0, dist_k2 =0;
    if(node == NULL)
	return -1;
 lca = lowCommAncesinBinTree(node, k1, k2);
  distOfNodeFromAkey(lca, 0, &dist_k1, k1);
  distOfNodeFromAkey(lca, 0, &dist_k2, k2);
return dist_k1 + dist_k2; 

}
/*to find lowest common ancestor of two nodes in a  BST(non-recursive)*/

TREE* lowest_common_ancestor(TREE* root, int node1, int  node2){
    TREE *temp,*temp1;
    temp = root;
    temp1=temp;

    if(root==NULL)
	return NULL;

    while(temp==temp1){
	if(node1 <= temp->value)
	    temp=temp->left;
	else
	    temp=temp->right;
	if(node2 <= temp1->value)
	    temp1=temp1->left;
	else
	    temp1=temp1->right;
    }
    /*At this point we have past the LCA, the parent of temp or temp1 is the LCA*/

    while (root->value != temp->value) {
	if(temp->value <= root->value) {
	    if(root->left->value == temp->value)
		break;
	    else 
		root=root->left;
	}
	else {
	    if(root->right->value == temp->value)
		break;
	    else 
		root=root->right;
	}
    }
    return root;
}

/* lowest common ancestor in BST (recursive) */

TREE *lcaBST(TREE *node, int k1, int k2){

    TREE* lnode, *rnode;
    if(node == NULL)
	return NULL;
    
    if( k1 < node->value  && k2 < node->value){
	
	lnode = lcaBST(node->left, k1, k2);
	return lnode;
    }
    else if (k1 > node->value && k2 > node->value){
	rnode = lcaBST(node->right, k1, k2);
	return rnode;
    }
    else 
	return node;
}

/*function to print the max height of a tree(not necessarily BST) 
Height : Max(height of left subtree,height of right subtree) + 1*/

int max_height ( TREE* node) {
    int h1,h2;

    if(node == NULL)
	return 0;
    h1 = max_height(node->left);
    h2 = max_height(node->right);
    if(h1 > h2)
	return(h1+1);
    else
	return(h2+1);
}
/* Print all nodes that are at distance k from a leaf node 
 * logic : 
 * 1.  we maintain an auxillary array path[] which stores the path of each leaf from root
 * 2.  we maintain a aux array visited[] which maintains if the node at level K is printed.
 * 3.  level ( to keep record of the levels) 
 */


void printNodeDistKUtil(TREE *node, int *path, int *visit, int level, int k) {

    if(node==NULL)
	return;
//store the path from root -> leaf in path array

    //clear the visited flag if we are replacing any old value
    if(path[level] && visit[level]){
	visit[level] = 0;
    }
    path[level] = node->value;
    level++;

    // if the node found is leaf , and the kth dist node is already not printed, then print it
    // and mark that node as visited
    if(node->left == NULL && node->right == NULL &&
	    level-k >=0) {

	if(!visit[level-k]){
	    printf("%d ",path[level-k]); 
	    visit[level-k] = 1;
	}
    }
    
    printNodeDistKUtil(node->left, path, visit, level, k);
    printNodeDistKUtil(node->right, path, visit, level, k);
}


void printNodeDistK(TREE *node, int k) {

    int max_h;
    int *path, *visit;

    max_h = max_height(node);

    path = (int*)malloc(sizeof(int)*max_h);
    visit = (int*)malloc(sizeof(int)*max_h);

    printNodeDistKUtil(node, path, visit, 0, k);

}


/* Transform a BST to greater sum tree 
 * http://www.geeksforgeeks.org/transform-bst-sum-tree/ */
void greaterSumBinTree(TREE *node, int *sum, int *temp) {

    if(node == NULL)
	return;

    greaterSumBinTree(node->right, sum, temp);
    *sum += *temp;
    *temp = node->value;
    node->value = *sum;
    greaterSumBinTree(node->left, sum, temp);

}


/*convert a tree into doubly link list: The rightmost node will become the new head
  Variation of reverse inorder*/

TREE* convert_to_d_lnk_list (TREE* node) {
    static TREE* temp = NULL;
    static	TREE *head;
    if (node == NULL )
	return node;

    convert_to_d_lnk_list (node->right);
    /* when the rightmost node is reached, store it in static head */
    if(temp == NULL) {

	head = node;
	temp = node;
    }
    else {
	if(node!=NULL){
	    node->right= temp;
	    temp->left = node;
	    temp = node;
	}
    }
    convert_to_d_lnk_list(node->left);
    /*return the static head*/
    return head;
}
/*Populate inroder successor for all nodes in a binary tree */
inorder_successor(TREE *node) {
    static TREE *temp = NULL;
    if(node == NULL)
	return ;

    inorder_successor(node->right);
    node->successor = temp;
    temp = node;
    inorder_successor(node->left);
}

//print inorder successor for a single node.

void inorder_successor_single_node ( TREE *node) {

}

/*print ancestors of a given node in a binary tree */

void print_ancestors(TREE *node) {

}

/*Program to delete all the nodes in a tree */

TREE* del_all_nodes( TREE * node) {
    /* variation for reverse inorder traversal; delete all nodes except the rightmost node and
       return it */
    static TREE* temp = NULL;
    if(node == NULL)
	return NULL;

    del_all_nodes(node->right);
    if(temp == NULL)
	temp = node;
    else{
	node->right == NULL;
	free(temp);
	temp = node;
    }
    del_all_nodes(node->left);
    return node;	
}

/*function to swap left and right children of a node */

void swap(TREE* node) {
    TREE* temp;
    temp = node->left;
    node->left=node->right;
    node->right = temp;
}

/*function to create a mirror image of a binary tree */

void mirror ( TREE* node ) {

    if(node == NULL )
	return;

    mirror(node->left);
    mirror(node->right);
    if(node->left!=NULL || node->right!=NULL)
	/*swap left and right children */
	swap(node);
}
/*another way of finding mirror */
void mirror1( TREE* node) {
    TREE * temp;
    if(node == NULL)
	return;
    if(!(node->left == NULL && node->right == NULL))
    {
	temp = node->right;
	node->right = node->left;
	node->left = temp;
    }
    mirror1(node->left);
    mirror1(node->right);

}
/*funtion to print all the nodes of a tree at a given level */

print_at_level ( TREE* node, int lvl, int level ) {


    if(node == NULL)
	return;
    if(level == lvl )
	printf("%d ",node->value);
    print_at_level(node->right,lvl+1,level);
    print_at_level(node->left,lvl+1,level);

}

/*level order printing of a tree using BFS*/

/*function to print the size(no of elements) of a tree*/

int size_of_tree(TREE* node){
    static int count;
    if (node == NULL)
	return 0;
    // print the inorder and keep the count. 
    size_of_tree(node->left);
    count++;
    size_of_tree(node->right);
    return count;
}

//get level of a node in Binary tree

int get_level(TREE *node, int val, int level) {
    static int lvl;

    if(node == NULL)
	return 0;
    if(node->value == val)
	lvl = level;


    get_level(node->left, val, level+1);
    get_level(node->right, val, level+1);

    return lvl;
}

//check if the tree is height_balanced or not.

int height_balanced(TREE *node, int ht) {
    int h1,h2;
    static int ret;
    if(node == NULL)
	return 0;

    h1 = height_balanced(node->left, ht+1);
    h2 = height_balanced(node->right, ht+1);

    if(abs(h1-h2) <= 1)
	ret = 1;

    return ret;

}

/* find index of the key in the inorder array */
int get_index(int *in, int key, int nodes){
    int i;

    for(i=0;i<nodes;i++){
	if(in[i] == key)
	    return i;
    }
}

/*
 *Construct Tree from given Inorder and Preorder traversals
 */

TREE* buildTree(int *in, int *pre, int low, int high, int nodes) {

    int  idx;
    static int j;
    TREE* node;

    if(pre == NULL || in == NULL)
	return NULL;

    node = create_node();
    node->value = pre[j];

    idx = get_index(in, pre[j], nodes);
    j++;
    if(low >= high)
	return node;

    node->left = buildTree(in, pre, low, idx-1, nodes);
    node->right = buildTree(in, pre, idx+1, high, nodes);

    return node;
}

/*
 *Print all nodes that don’t have sibling
 *http://www.geeksforgeeks.org/print-nodes-dont-sibling-binary-tree/
 */

void printNoSibling(TREE* node, TREE** parent){

    if(node == NULL)
	return;

    if(*parent) {
	if((*parent)->left && (*parent)->right == NULL){
	    printf("%d\n", node->value);
	} else if((*parent)->right && (*parent)->left == NULL){
	    printf("%d\n", node->value);
	}
    }
    printNoSibling(node->left, &node);
    printNoSibling(node->right, &node);
}

/*
 *convert a tree in doubly link list (elegant method)
 */

void convertToDLL(TREE* node, TREE** ins){

    if(node == NULL)
	return;

    convertToDLL(node->right, ins);
    if(*ins == NULL){
	*ins = node;
    } else {
	node->right = *ins;
	(*ins)->left = node;
	*ins = node;
    }
    convertToDLL(node->left, ins);
}

/*
 * Deepest left leaf node in a binary tree
 * http://www.geeksforgeeks.org/deepest-left-leaf-node-in-a-binary-tree/
 */

void deepestLeftLeafNode(TREE* node, TREE** parent, int lvl, int *lln){

    static int maxht;

    if(node == NULL)
	return;

    deepestLeftLeafNode(node->left, &node, lvl+1, lln);
    if(lvl > maxht && (*parent)->left == node){
	maxht = lvl;
	*lln = node->value;
    }
    deepestLeftLeafNode(node->right, &node, lvl+1, lln);

} 

int min_depth(TREE *node) {

    int lefth, righth;
    if(node == NULL)
	return 0;

    lefth = min_depth(node->left);
    righth = min_depth(node->right);

    //if any of the left or right child is null
    if(lefth == 0 || righth == 0)
	return MAX(lefth, righth)+1;

    return MIN(lefth, righth)+1;

}

int main() {
    char c;
    int item,value,num,node1,node2,level,n;
    TREE  *trav;
    TREE *prev=NULL;
    int a,choice;
    int key;
    int key1,key2;
    int i,no;
    int nodes;
    int *in, *pre;
    TREE *parent;
    TREE *node;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- insert\t");
	printf("2 -- print inorder\t");
	printf("3 -- find\t");
	printf("4 -- delete\t");
	printf("5 -- Minimum\t");
	printf("6 -- Inorder successor in binary tree\t");
	printf("7 -- Convert to a singly link list\t");
	printf("8 -- Is BST\t");
	printf("9 -- Convert to a doubly link list\t");
	printf("10 -- Maximum element in a binary tree\t");
	printf("11 -- Inorder Successor\t");
	printf("12 -- Max height(depth) of a tree\t");
	printf("13 -- Delete all nodes\t");
	printf("14 -- Lowest common Ancestor in BST\t");
	printf("15 -- Mirror image of a binary tree\t");
	printf("16 -- Print elements at a given level\t");
	printf("17 -- Print the size(no of elements) of a tree\t");
	printf("18 -- get level of node of a tree\t");
	printf("19 -- Check if the tree is height balanced.\t");
	printf("20 -- print ith order statistic-using inorder\t");
	printf("21 -- remove all half nodes\t");
	printf("22 -- Level order traversal(BFS) of a tree\t");
	printf("23 -- Check if a binary tree is Complete\t");
	printf("24 -- Sum of all left leaf trees\t");
	printf("25 -- Remove nodes on leaf paths\t");
	printf("26 -- Find node in a binary tree\t");
	printf("27 -- Convert to binary threaded tree\t");
	printf("28 -- Check for cousins in a binary tree\t");
	printf("29 -- Inorder successor in BST\t");
	printf("30 -- Maximum sum leaf to root path in a Binary Tree\t");
	printf("31 -- Maximum path sum between two leaves of a binary tree\t");
	printf("32 -- Reverse altenate levels of a perfect binary tree\t");
	printf("33 -- Lowest common ancestor in Binary tree\t");
	printf("34 -- Distance between two given keys in a binary tree\t");
	printf("35 -- Transform a BST to greater sum tree\t");
	printf("36 -- Construct Binary Tree from given Inorder and Preorder traversals\t");
	printf("37 -- Print all nodes at distance k from a given node\n");
	printf("38 -- Print all nodes that are at distance k from a leaf node\n");
	printf("39 -- Print all nodes that don’t have sibling\n");
	printf("40 -- Convert to Doubly link list(method 2)\n");
	printf("41 -- Deepest left leaf node in a binary tree\n");
	printf("42 -- Minimum depth of the tree\n");
	

	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter no of nodes\n");
		scanf("%d", &no);

		for(i=0;i<no;i++) {
		printf("Enter  element\n");
		scanf("%d",&item);
		insert_node(root,item);
		}
		break;
	    case 2:
		trav = root;
		if(trav!=NULL)
		    print_inorder(trav);
		else
		    printf("Tree is empty");
		break;
	    case 3:
		trav = root;
		printf("Enter the element to be searched\n");
		scanf("%d",&a);
		node = find_node(trav,a);
		if(node)
		    printf("Node found");
		else
		    printf("Node not found");
		break;
	    case 5:
		trav = root;
		find_minimum(trav);
		break;
	    case 6:
		printf("Enter the number\n");
		scanf("%d", &num);
		trav = root;
		if(trav!=NULL)
		    printf("Successor : %d\n",printSuccessorInBinTree(trav,num));
		else
		    printf("Tree is empty");
		break;
	    case 7:
		trav = root;
		TREE **p = NULL;
		bst_to_s_lnklist(trav,p);
		//print doubly link list
		while(trav!=NULL){
		    printf("%d-->",trav->value);
		    trav = trav->left;
		}
		break;
	    case 8:
		trav = root;
		printf("%d\n",is_bst(trav));
		break;
	    case 9:
		trav = root;
		trav = convert_to_d_lnk_list(trav);
		/*printing the list */
		while(trav!=NULL){
		    printf("%d ",trav->value);
		    trav=trav->left;
		}
		break;
	    case 10:
		trav = root;
		trav = find_maximum(trav);
		printf("Maximum : %d\n", trav->value);
		break;
	    case 11:
		trav = root;
		if(trav!=NULL)
		    inorder_successor(trav);
		else
		    printf("Tree is empty");
		break;
	    case 12:
		printf("Max height %d\n",max_height(root));
		break;

	    case 13:
		trav = root;
		trav = del_all_nodes(trav);
		free(trav);
		print_inorder(trav);
		break;
	    case 14:
		printf("Enter the first number\n");
		scanf("%d", &node1);
		printf("Enter the second number\n");
		scanf("%d", &node2);
		trav = root;
		/*trav = lowest_common_ancestor(trav,node1,node2);*/
		trav = lcaBST(trav,node1,node2);
		printf("LCA : %d\n",trav->value);
		break;
	    case 15:
		trav = root;
		mirror1(trav);
		print_inorder(trav);
		printf("Inorder is not sorted,ie mirror tree is no longer a binary tree\n");
		break;
	    case 16:
		printf("Enter  level\n");
		scanf("%d",&level);
		print_at_level(root,0,level);
		break;
	    case 17:
		trav = root;
		printf("Size:%d\n",size_of_tree(trav));
		break;
	    case 18:
		trav = root;
		printf("Enter the node\n");
		scanf("%d", &num);
		printf("Size:%d\n",get_level(trav,num,1));
		break;
	    case 19:
		trav = root;
		printf("Height Balanced:%d\n",height_balanced(trav, 1));
		break;
	    case 20:
		trav = root;
		printf("enter ith order statistics\n");
		scanf("%d", &n);
		printf("%dth order statistics:%d\n",n,Kth_order_stats_usingInoder(trav, n));
		break;
	    case 21:
		printf("Remove half nodes\n");
		trav = root;
		trav = removeHalfNodes(trav, NULL);
		    print_inorder(trav);
		/*printf("%dth order statistics:%d\n",n,Kth_order_stats_usingInoder(trav, n));*/
		break;
	    case 22:
		printf("Level order Traversal(BFS)\n");
		trav = root;
		int height;
		LIST *list;
		height = max_height(trav);
		printf("height = %d\n", height);
		list  = (LIST*)calloc(sizeof(LIST), height);
		level_order_tree(trav, 0, list);
		print_level_order(list, height);
		break;

	    case 23:
		trav = root;
		int no_of_nodes;
		no_of_nodes = count_nodes(trav);
		printf("Tree %s complete binary tree\n", isBinaryTreeComplete(trav, 0, no_of_nodes)?"is":"is not");
		break;

	    case 24:
		trav = root;
		printf("Sum of all left leaf trees: %d\n", countLeftLeafSum(trav, NULL));
		break;

	    case 25:
		trav = root;
		int k;
		printf("Enter the number K\n");
		scanf("%d",&k);
		removeNodesOnLeafPaths(trav, 1, NULL, k);
		print_inorder(trav);
		break;

	    case 26:
		trav = root;
		TREE *temp;
		printf("Enter the key\n");
		scanf("%d",&key);

		if((temp = findNodeInBinaryTree(trav, key))!=NULL){
		    printf("Node found %d", temp->value);
		}
		else
		    printf("Node not found");

		break;

	    case 27:
		trav = root;
		TREE* in_prev = NULL;
		convertToThreadedBinTree(trav, &in_prev);
		printThreadedBintree(trav);
		break;

	    case 28:
		trav = root;
		int n1, n2;
		printf("Enter node 1\n");
		scanf("%d", &n1);
		printf("Enter node 2\n");
		scanf("%d", &n2);
		
		printf("%s\n", checkCousins(trav, n1, n2, 0, NULL)?"cousins":"not cousins"); 

	    case 29:
		trav = root;
		int key;
		printf("Enter the key\n");
		scanf("%d",&key);

		printf("Inorder Successor = %d\n", inOrderSuccInBST(trav, key));
		break;

	    case 30:
		trav = root;
		printf("Max sum from root to leaf = %d\n", maxLeafToRootSum(trav));
		break;

	    case 31:
		trav = root;
		int maxSum = 0;
		maxSumTwoLeaves(trav, &maxSum);
		printf("maximum path sum between two leaves of a binary tree= %d", maxSum);
		break;

	    case 32:
		trav = root;
		reverseAlternateLevels(trav->left, trav->right, 0);
		print_inorder(trav);
		break;

	    case 33:
		trav = root;
		printf("Enter key1\n");
		scanf("%d", &key1);
		printf("Enter key2\n");
		scanf("%d", &key2);
		printf("LCA in Binary Tree = %d\n",lowCommAncesinBinTree(trav, key1, key2)->value);
		break;
		
	    case 34:
		trav = root;
		printf("Enter key1\n");
		scanf("%d", &key1);
		printf("Enter key2\n");
		scanf("%d", &key2);
		printf("Distance between the keys = %d\n", distBetweenKeys(trav, key1, key2));
		break;

	    case 35:
		trav = root;
		int tmp = 0, sum = 0;
		greaterSumBinTree(trav, &tmp, &sum);
		print_inorder(trav);
		break;

	    case 36:
		printf("Enter number of nodes\n");
		scanf("%d", &nodes);

		in = (int*)malloc(sizeof(int)*nodes);
		pre = (int*)malloc(sizeof(int)*nodes);

		printf("Enter inorder traversal\n");
		for(i=0;i<nodes;i++){
		    scanf("%d", &in[i]);
		}
		printf("Enter preorder traversal\n");
		for(i=0;i<nodes;i++){
		    scanf("%d", &pre[i]);
		}
		 TREE* trav;
		trav = buildTree(in, pre, 0, nodes-1, nodes);
		print_inorder(trav);
		break;

	    /*case 37:*/

		/*break;*/

	    case 39:
		trav = root;
		parent = NULL;
		printNoSibling(trav, &parent);
		break;

	    case 40:
		trav = root;
		TREE *ins;
		ins = NULL;

		convertToDLL(trav, &ins);
		while(ins!=NULL){
		    printf("%d-->",ins->value);
		    ins = ins->right;
		}
		break;

	    case 41:
		trav = root;
		int lln = 0;
		parent = NULL;
		deepestLeftLeafNode(trav, &parent, 0, &lln);
		printf("%d", lln);
		break;

	    case 42:
		trav = root;
		printf("Minimum depth of tree: %d\n", min_depth(trav));
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

