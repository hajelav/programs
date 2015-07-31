#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "binary_tree.h"


void create_nStairsTree(NODE* node, int n) {

    if(node==NULL)
	return;
    if(n==0)
	return;

    node->left = create_node(node->val+1);
    create_nStairsTree(node->left, n-1);

    node->right = create_node(node->val+2);
    create_nStairsTree(node->right, n-1);
}

NODE *create_node(int val) {

    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->left = NULL;
    node->right = NULL;
    node->val = val;
}
