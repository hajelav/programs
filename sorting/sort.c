#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int* create_1Darray(int n) {
    int *A;
    A = (int*)calloc(n, sizeof(int));

    if(!A)
	return NULL;
    return A;
}

void input_array(int *A, int n) {
    int i;
    printf("Enter elements\n");
    for(i=0;i<n;i++){
	scanf("%d", &A[i]);
    } 
}

void print_1Darray(int *A, int n) {
    int i;
    for(i=0;i<n;i++){
	printf("%d ", A[i]);
    } 
}

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
    /*A[idx1] = A[idx1] + A[idx2];*/
    /*A[idx2] = A[idx1] - A[idx2];*/
    /*A[idx1] = A[idx1] - A[idx2];*/
}

void merge(int *A, int l, int i, int j, int h){
    int *T, k;
    int low, high;
    if(l>=h)
	return;
    low = l;
    high = h;
    T = (int*)malloc(sizeof(int)*(h-l+1));

    k=0;
    while(l<=i && j<=h){
	if(A[l] < A[j]){
	    T[k] = A[l];
	    l++;
	} else if (A[l] > A[j]){
	    T[k] = A[j];
	    j++;
	} else {
	    T[k] = A[l];
	    l++;
	    j++;
	}
	k++;
    }

    //first half is bigger
    if(l<=i){
	while(l<=i){
	    T[k] = A[l];
	    l++;
	    k++;
	}

    } else if(j<=h) { //second half is bigger
	while(j<=h){
	    T[k] = A[j];
	    j++;
	    k++;
	}
    }

    //copy the temp array to A
    k=0;
    while(low <= high){
	A[low] = T[k];
	k++;
	low++;
    }
    free(T);
}

/*mergesort : divide and conquer paradigm*/
void mergesort(int *A, int low, int high) {

    int mid;
    if(low >= high)
	return;

    mid = (low+high)/2;

    mergesort(A, low, mid);  //mergesort on left array
    mergesort(A, mid+1, high); //mergesort on right array

    //merge the array from low to low mid, and mid+1 to high)
    merge(A, low, mid, mid+1, high);
}

/*
 *returns the number of inversion spanning across the two sorted arrays
 */
int merge_and_count_inv( int *A, int l, int i, int j, int h) {

    int count = 0;
    if(l>=h)
	return 0;

    while(l<=i && j<=h){
	if(A[l] < A[j]){
	    l++;
	} else if (A[l] > A[j]){
	    /*
	     *we have found an element in the first array which is greater thaan second array. so 
	     *count = 1 + no of elements after lth element( this is because we have already found an element
	     *in first array which is greater than the element in the second array,and since the array is 
	     *sorted. All other elements after this element will also be greater.	
	     */
	    count = count + i-l+1;
	    j++;
	} else {
	    l++;
	    j++;
	}
    }

    return count;
}

/*
 *Idea : to calculate the split inversion, we sort each arrays  first and run the merge routing.
 *The merge routine actually calculates the split inversions in the array, ie whenever we find a smaller element we 
 *add it to the temp array, and increase the split count by 1
 */

int split_inversion(int *A, int l, int i, int j, int h) {

    if (l>=h)
	return 0;
    //mergesort the two halves first
    mergesort(A, l, i);  //mergesort on left array
    mergesort(A, j, h); //mergesort on right array

    return merge_and_count_inv(A, l, i, j, h);

}

/*
 *counting inversions : divide and conquer paradigm
 *Using divide and conquer, we divide the array into two parts.
 *1. calculate the inversions in the first half
 *2. calculate the inversions in second half
 *3. calculate the in inversions spanning across two array(split inversions)
 *4. total inversions = sum 1 + sum 2 + sum 3
 *5. Recurse the solution for till the size of the array becomes  one (it low>=high)
 */


int count_inversion(int *A, int low, int high) {

    int mid;
    int leftInv, rightInv, totInv ;

    if(low>=high)
	return 0;
    mid = (high+low)/2;

    leftInv = count_inversion(A, low, mid);
    rightInv= count_inversion(A, mid+1, high);
    totInv = leftInv + rightInv + split_inversion(A, low, mid, mid+1,  high);

    return totInv;
}

int partition(int *A, int l, int h) {

    int i, j, k, s;

    j = 0; //points to the start of temp array T
    k = h-l; //points to the end of temp array T
    s = l; //store the lower index of array


    //create a temp array 
    int *T = (int*)calloc(h-l+1, sizeof(int));
    for(i=l+1;i<=h;i++){
	if(A[i] > A[l]){
	    T[k] = A[i];
	    k--;
	} else {
	    T[j] = A[i];
	    j++;
	}
    }

    //now fill the piv at the right place at the temp array
    T[j] = A[l];

    //copy the temp array back to input array A
    k=0;
    while(l <= h){
	A[l] = T[k];
	k++;
	l++;
    }
    free(T);
    return s+j;
}

void quicksort(int *A, int low, int high) {

}

int order_statistic(int  *A, int low , int high, int st) {


    int piv, ret;
    int j; //index of pivot element after partitioning

    if(st > high) 
	return -1;
    if(low == high)
	return A[low];

    srand(time(NULL));
    /*generate the random number between low to high+1(no of elements in array to be considered)*/
    /*piv = rand()%(high+1);*/
    piv = low;
    printf("random pivot: %d\n",piv); 

   /*preprocess the array and swap the elements of 0th and piv */
    printf("before swap\n"); 
    print_1Darray_index(A, low, high);
    swap(A, low, piv);
    printf("after swap\n"); 
    print_1Darray_index(A, low, high);


    /*partition the array so that the random pivot is at its correct position in array*/
     j = partition(A, low, high);
    printf("partition idx: %d\n",j); 
    printf("After partition: %d\n",j); 
    print_1Darray_index(A, low, high);
    printf("-----------------------\n");
    /*if we are in luck to get the random pivot as the desired ith order stats then return it*/
    if(st == j){
    return A[j];
    }

    /*
     *if the pivot index(j) is greater than st(ith order statistic), then we need to recurse the array , right of pivot
     *    ie, from j+1 to high and find st-j order stats  
     */
    if(st>j)
    ret = order_statistic(A, j+1, high, st);
    else 
    ret = order_statistic(A, low, j-1, st);

    return ret;
}

int main() {
    char c;
    int choice, n, s;
    int *A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Mergesort in an array\t");
	printf("2 -- Counting inversions in an array(divide and conquer method)\t");
	printf("3 -- Quicksort\t");
	printf("4 -- ith order statistics\t");

	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);

		mergesort(A, 0, n-1);
		print_1Darray(A, n);
		free(A);
		break;

	    case 2:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Inversions :%d\n", count_inversion(A, 0, n-1));
		free(A);
		break;

	    case 3:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		quicksort(A, 0, n-1);
		break;

	    case 4:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Enter ith order statistic\n");
		scanf("%d", &s);
		// to find s order statistic we need to find the element in index n-s
		printf("%d order statistic:%d\n", s, order_statistic(A, 0, n-1, n-s));
		free(A);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

