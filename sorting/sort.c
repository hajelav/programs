#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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




int main() {
    char c;
    int choice, n;
    int *A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Mergesort in an array\t");
	printf("2 -- Counting inversions in an array\t");

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

		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

