#include <assert.h>
typedef struct node {
    int val;
    struct node *left;
    struct node *right;
}NODE;

void create_nStairsTree(NODE*, int n);
NODE *create_node(int val);
