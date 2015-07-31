#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "binary_tree.h"

int waysToReach( NODE* node, int nStairs) {
    static int count;
    if(node==NULL)
        return;

    waysToReach(node->left, nStairs);

    if(node->val == nStairs){
        count++;
    }
    waysToReach(node->right, nStairs);

    return count;
}


int main(int argc, char* argv[]) {

    NODE* node;
    int nWays;

    if(!argv[1]) {
        printf("Provide no of stairs\n");
        exit(0);
    }
    nWays = atoi(argv[1]);
    //create a root node
    node = create_node(0);

    if(node!=NULL){
        create_nStairsTree(node, nWays);

    }
    printf("Ways to reach %d stairs=%d\n", nWays, waysToReach(node, nWays));
    return 0;

}
