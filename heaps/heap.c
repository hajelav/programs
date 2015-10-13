#include "../utils.h"

int *A;
/*function pointer of min/max heapify functions*/
typedef void (*HEAPIFY)(int*, int , int); 


/*int* create_1Darray(int n) {*/
    /*int *A;*/
    /*A = (int*)calloc(n, sizeof(int));*/

    /*if(!A)*/
	/*return NULL;*/
    /*return A;*/
/*}*/

/*void input_array(int *A, int n) {*/
    /*int i;*/
    /*printf("Enter elements\n");*/
    /*for(i=0;i<n;i++){*/
	/*scanf("%d", &A[i]);*/
    /*} */
/*}*/


void print_1Darray_index(int *A, int i, int j){
int k;
    for(k=i;k<=j;k++){
	printf("%d ", A[k]);
    } 
    printf("\n");
}

void swap(int *A, int idx1, int idx2) {
    int temp;
   temp = A[idx1];
   A[idx1] = A[idx2];
   A[idx2] = temp;
}

int MAX_heap(int *A, int a, int b) {
    return A[a]>A[b]?a:b;
}
int MIN_heap(int *A, int a, int b) {
    return A[a]>A[b]?b:a;
}

/*returns the index of max node between parent,left child and right child*/
int max_heap_node(int *A, int a, int b, int c) {

    //when leaf node , return the idx of parent
    if(b<0 && c<0)
	return a;
    //when left child is NULL and right child is not NULL
    if(b<0 && c>0)
	return MAX_heap(A, a, c);
    //when right child is NULL and left child is not NULL
    if(c<0 && b>0)
	return MAX_heap(A, a, b);

    if((A[a]-A[b] >= 0) && (A[a]-A[c] >=0))
	return a;
    else if(A[b]-A[a] >= 0 && A[b]-A[c] >= 0 )
	return b;
    else 
	return c;
}


/*returns the index of min node between parent,left child and right child*/
int min_heap_node(int *A, int a, int b, int c) {

    //when leaf node , return the idx of parent
    if(b<0 && c<0)
	return a;
    //when left child is NULL and right child is not NULL
    if(b<0 && c>0)
	return MIN_heap(A, a, c);
    //when right child is NULL and left child is not NULL
    if(c<0 && b>0)
	return MIN_heap(A, a, b);

    if(A[a]-A[b] <= 0 &&A[a]-A[c] <=0)
	return a;
    else if(A[b]-A[a] <= 0 && A[b]-A[c] <= 0 )
	return b;
    else 
	return c;
}

/*get the left child index*/
int get_left_child(int i) {
    return 2i+1;
}

/*get the left child index*/
int get_right_child(int i) {
    return 2i+2;
}

int get_parent(int i) {
    
    if(i==0) 
	return -1;
    return (i-1)/2;
}

/* get the index(idx) to the coorect place so that it satisfies max heap property */
void max_heapify(int *A, int size, int idx) {

    int lchild, rchild;
    int max_idx;

    lchild = (2*idx+1 <= size)?2*idx+1:-1;
    rchild = (2*idx+2 <= size)?2*idx+2:-1;

    /*
     *return when we reach to the leaf, ie when both the 
     *left child and right child of a node becomes NULL(ie when idx becomes > size of the array)
     */
    if(lchild < 0 && rchild < 0)
	return;

    max_idx = max_heap_node(A, idx, lchild, rchild);

    /*swap the index of max node with current index*/
    swap(A, idx, max_idx);

    /*recurse again on the max_idx when the max index is not equal to parent node*/
    if(max_idx!=idx)
    max_heapify(A, size, max_idx);
}

/* get the index(idx) to the coorect place so that it satisfies min heap property */
void min_heapify(int *A, int size, int idx) {

    int lchild, rchild;
    int min_idx;

    lchild = (2*idx+1 <= size)?2*idx+1:-1;
    rchild = (2*idx+2 <= size)?2*idx+2:-1;

    /*
     *return when we reach to the leaf, ie when both the 
     *left child and right child of a node becomes NULL(ie when idx becomes > size of the array)
     */
    if(lchild < 0 && rchild < 0)
	return;

    min_idx = min_heap_node(A, idx, lchild, rchild);

    /*swap the index of max node with current index*/
    swap(A, idx, min_idx);

    /*recurse again on the max_idx when the max index is not equal to parent node*/
    if(min_idx!=idx)
    min_heapify(A, size, min_idx);
}


/*
 *the build heap procedure make sure that the whole array satisfies the heap(min/max) property.
 *In order to do that , we run our heapify procedure for all non-leaf nodes
 */
void build_heap(int *A, int n, HEAPIFY fptr) {

   int i;
   i = n/2;
   while(i >= 0){
       //call min or max heapify function
       (*fptr)(A, n, i);
       i--;
   }
}

/*
 *to sort the array -
 *1. we build a heap(say max heap), so that the first element in the build heap is always the largest
 *2. exchance the max(first) element with the last one
 *3. Now only the exchanged element(first one) violates the heap property, so
 *4. just run heapify on the first element.
 *5. decrease the size of array and recurse 
 */
void heapsort(int *A, int n ) {

    HEAPIFY fptr = max_heapify;
    build_heap(A, n, fptr);

    while(n>0){
	swap(A, 0, n);
	n--;
	max_heapify(A, n, 0);
    }
}

void median(){
/*http://algorithmsandme.com/2014/08/heaps-find-median-of-stream-of-integers*/
/*http://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers*/

/*
 * Algorithm:
 *For the first two elements add smaller one to the maxHeap on the left, and bigger one to the minHeap on the right. Then process stream data one by one,
 *
 *Step 1: Add next item to one of the heaps
 *
 *      if next item is smaller than maxHeap root add it to maxHeap,
 *      else add it to minHeap
 *
 * Step 2: Balance the heaps (after this step heaps will be either balanced or
 *                                     one of them will contain 1 more item)
 *
 *      if number of elements in one of the heaps is greater than the other by
 *       more than 1, remove the root element from the one containing more elements and
 *       add to the other one
 *
 *      Then at any given time you can calculate median like this:
 *        If the heaps contain equal elements;
 *        median = (root of maxHeap + root of minHeap)/2
 *        Else
 *     median = root of the heap with more elements
 */

    //To be implemented

}


/*
 *k-way merge sort 
 * leetcode problem 23
 * https://leetcode.com/problems/merge-k-sorted-lists/
 *http://stackoverflow.com/questions/10414255/prove-the-algorithm-that-uses-min-heap-to-merge-k-sorted-lists
 */

void k_way_merge_sort() {

    int i, n, n1;
    int **A;
    /*int *H; // heap*/
    printf("enter number of sorted arrays to merge\n");
    scanf("%d", &n);
    A = create_1D_array_ptr(n);


    /*input all the arrays*/
    for(i=0;i<n;i++) {
	printf("enter number of elements for array %d\n", i);
	scanf("%d", &n1);
	//create an array
	A[i] = create_1Darray(n1);
	input_array(A[i], n1);
    }

    /*to do k way mergesort , we need a heap of size n(equal to number of arrays)*/
	/*H = create_1Darray(n);*/
	//TBD

}


/*
 * facebook-interview-questions
 * Given a list of n objects, write a function that outputs the minimum set of numbers that sum to at least K. (better than NLOGN)
 *
 *    1. create a max heap in O(n) time
 *    2. extract the max element from the heap (say max)
 *    3. if max>K then return 1;
 *    4  otherwise decrease the size of heap by 1 and search for K-max in the  left heap (n-1)
 *    5. update K = K-max
 *    6. goto step 2 , until K = max
 *    7. while looping continue the no of times the max was updated. this is the min no of element required.8*/

/*
 *google interview questions
 *http://www.careercup.com/question?id=5658326589243392
 *Given a max-heap represented as an array, return the kth largest element without modifying the heap. I was asked to do it in linear time, but was told it can be done in log time.
 *
 *algorithm :
 *1. Let A be the the orginal max-heap array
 *2. Initially queue is empty and rank = 0
 *3. Insert root(max element of A) in queue
 *4. while(Queue!= empty){
 *
 * //add queue currents node's left  and right child to the queue
 * enqueue(leftchild);
 * enqueue(rightchild);
 * //heapify the queue
 * heapify(Queue);
 *
 * //delete node from queue (deletion is done from front and insertion from tail, like BFS)
 * dequeue(Queue);
 *
 * rank++;
 *
 * if(rank == ith order statsictic)
 *     return the dequeued element
 *
 *}
 *
 *complexity : since to find Kth largest we atleast need to dequeue K element , and for each element , we need to heapify the 
 *queue which take log(n) time , n-> no of elements in the queue at a given time,
 *      so total time = Klog(n)
 */


/*
 *http://www.careercup.com/question?id=16759664 [google interview question]
 *You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists. 
 *
 *For example, 
 *    List 1: [4, 10, 15, 24, 26] 
 *    List 2: [0, 9, 12, 20] 
 *    List 3: [5, 18, 22, 30] 
 *
 *    The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.
 *
 * Approach: this can be done using a variant of k-way merge sort(using heap). we maintain a heap of size K , and keep on adding elements onto
 * the heap as k-way merge sort. Also in the heap we maintain the difference between min and max as we go along. Finally when we are done adding
 * elements into the heap, we return output as the the min max value of the smallest diff.
 */

int main() {
    char c;
    int choice, n;
    HEAPIFY f; // function pointer to max_heapify or min_heapify
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Enter the array\n");
	printf("2 -- max-heapify(max element stays on top)\n");
	printf("3 -- min-heapify(min element stays on top)\n");
	printf("4 -- heapsort\n");
	printf("5 -- Find median of stream of integers\n");
	printf("6 -- K-way mergesort using min heap\n");

	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		break;
	    case 2:
		f = max_heapify;
		build_heap(A, n-1, f);
		print_1Darray(A, n);
		break;

	    case 3:
		f = min_heapify;
		build_heap(A, n-1, f);
		print_1Darray(A, n);
		break;

	    case 4:
		heapsort(A, n-1);
		print_1Darray(A, n);
		break;
		
	    case 5:
		median();
		break;

	    case 6:
		k_way_merge_sort();
		break;


	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
