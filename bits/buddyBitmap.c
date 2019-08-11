/*
* https://github.com/jasonfeng1989/Tech_Interviews/blob/master/others/buddy_bitmap.py
*
* pure storage buddy system bitmap
* Given a complete binary tree with nodes of values of either 1 or 0, the following rules always hold:
*(1) a node's value is 1 if and only if all its subtree nodes' values are 1
*(2) a leaf node can have value either 1 or 0
*Implement the following 2 APIs:
*set_bit(offset, length), set the bits at range from offset to offset+length-1
*clear_bit(offset, length), clear the bits at range from offset to offset+length-1
*/

#include "../utils.h"


void print_1Darray(int *A, int  n){
    int i;
    for(i=0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int getLeftChildIndex(int *A, int i, int sizeA){
    
    if(2*i+1 < sizeA)
        return (2*i+1);
    return -1;
}
int getRightChildIndex(int *A, int i, int sizeA){

    if(2*i+2 < sizeA)
        return (2*i+2);
    return -1;
}

int getParentIndex(int *A, int i){
    
    if(i>0){
        return (i-1)/2;
    } else
        return -1;
}

int getSiblingIndex(int *A, int i, int sizeA) {

    int p, l, r;
    p = getParentIndex(A, i);
    if(p<0)
        return -1; //root does not have sibling
    
    //check if sibling is left child
    r = getRightChildIndex(A, p, sizeA);
    if(r<0)
        return -1; //no right sibling
    l = getLeftChildIndex(A, p, sizeA);
    if(l<0)
        return -1; //no left sibling
    
    if(i != r)
        return r;
    return l;


}

void setBitDown(int *A, int i, int sizeA) {
    int l, r;

    if(i < 0)
        return;


    A[i] = 1;
    l = getLeftChildIndex(A, i, sizeA);
    r = getRightChildIndex(A, i, sizeA);
    setBitDown(A, l, sizeA);
    setBitDown(A, r, sizeA);

}

void setBitUp(int *A, int i, int sizeA) {

    int sibIndex, parentIndex;
    while(i > 0) {
        sibIndex = getSiblingIndex(A, i, sizeA);
        if(A[sibIndex] == 0)
            break;
        parentIndex = getParentIndex(A, i);
        printf("setting sibling at index %d to 1\n", parentIndex);
        A[parentIndex] = 1; //set the parent index 
        i = parentIndex; //make i the new parent

    }//while ends
     
}


void setBit(int *A, int off, int len, int sizeA){

    int i;
    if(off < 0 || (off+len-1 >= sizeA))
            return;

    //loop through the range starting from off and ending at off+len-1
    for(i=off; i<=(off+len-1); i++) {

        //if the bit is already set, then ignore it
        if(A[i] == 1)
            continue;

        /* set the bit at pos i to 1. after that we need to do 2 steps
         * 1. we need to travel down the tree and make sure all the bits below tree rooted at i are 1
         * 2. since we have turned on the bit at i, we also need to see , if any path up to the root also needs to be set to 1 ?.
         * To do this we go to sibling(i), and if its 1 then we set parent(i) to 1. Repeat this on the path to the root, till the time 
         * you find a sibling which is set to 1
         * */

        //1. set bit in downward direction
        setBitDown(A, i, sizeA);

        //2. set bit in upwards direction
        setBitUp(A, i, sizeA);

    }
}

void clearBitUp(int *A, int i) {

    int parentIndex;
    while(i > 0) {
        parentIndex = getParentIndex(A, i);

        if(A[parentIndex] == 0)
            break;
        printf("setting sibling at index %d to 0\n", parentIndex);
        A[parentIndex] = 0; //set the parent index 
        i = parentIndex; //make i the new parent
    }


}


void clearBit(int *A, int off, int len, int sizeA){

    int i;
    if(off < 0 || (off+len-1 >= sizeA))
        return;

    //loop through the range starting from off and ending at off+len-1
    for(i=off; i<=(off+len-1); i++) {

        //if the bit is aleady set to 0, ignore it
        if(A[i] == 0)
            continue;

        A[i] = 0;
        //move in up direction--> we have to set all nodes which are 1, to 0 from i to root
        clearBitUp(A, i);

        //since we are setting bit from 1 to 0, we need to set at least one bit to 0 in the downward direction, we can do
        //this by either making all letf or right childs to be zero

        //clearBitDown(A, i); --> TBD

    }//for ends
    


}


/*
 *this is the API to set the bit in the bitmap. It returns the index of the first available bit which 
 *can be set. 
 */



int set_bit( int *A, int size, int i) {

    int left, right;

    /*if the bit is already set then return*/
    if(A[i] == 1)
        return -1;

    /*if you reach to an index which doesnt exist , then return*/
    if(i >= size)
        return -1;

    /*recurse the left subtree*/
    left = set_bit(A, size, 2*i+1);
    /*recurse the right subtree*/
    right = set_bit(A, size, 2*i+2);

    /*if left subtree is filled and right has an empty slot*/
    if((left < 0) && (right > 0))
        return right;
    /*if right subtree is filled and left has an empty slot*/
    else if((right < 0) && (left > 0))
        return left;
    /*if both left and right subtree has empty slots*/
    else if((left > 0) && (right > 0))
        return left;
    /*if an empty slot exists, then return its index*/
    else if(A[i] == 0)
        return i;
    else
        return -1;

}


int main() {

    int i;
    int *A;
    int idx;

    /*printf("enter array len\n");*/
    /*scanf("%d", &n);*/

    A =  (int*)malloc(sizeof(int)*12);
    for(i=0; i< 12; i++) {
        A[i] = 0;
    }
        
    /*
     *printf("enter array\n");
     *for(i=0;i<n;i++){
     *    scanf("%d", &A[i]);
     *}
     */
    printf("\n");

    print_1Darray(A, 12);
    idx = set_bit(A, 12, 0);
    printf("idx = %d\n", idx);
    A[idx] = 1;
    idx = set_bit(A, 12, 0);
    printf("idx = %d\n", idx);
    A[idx] = 1;
    idx = set_bit(A, 12, 0);
    printf("idx = %d\n", idx);
    A[idx] = 1;
    idx = set_bit(A, 12, 0);
    printf("idx = %d\n", idx);
    //setBit(A, 9, 2, n);
    /*clearBit(A, 1, 2, n);*/
    print_1Darray(A, 12);
    free(A);
    return 0;
}
