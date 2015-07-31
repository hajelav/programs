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


/*counting inversions : divide and conquer paradigm*/

int count_inversions(int *A, int low, int high) {

    int mid;
    mid = (high+low)/2;



}




int main() {
    char c;
    int choice, n;
    int *A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Mergesort in an array\t");
	printf("1 -- Counting inversions in an array\t");
	printf("1 -- Mergesort\t");

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
		printf("Inversions :%d\n", count_inversions(A, 0, n-1));

		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

