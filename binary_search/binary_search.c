#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

/*function pointer of min/max heapify functions*/


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

void swap(char *A, int idx1, int idx2) {
    int temp;
   temp = A[idx1];
   A[idx1] = A[idx2];
   A[idx2] = temp;
}

int MAX(int *A, int a, int b) {
    return A[a]>A[b]?a:b;
}
int MIN(int *A, int a, int b) {
    return A[a]>A[b]?b:a;
}

char * create_string(int len){
    char *str;
    str = (char*)malloc(sizeof(char)*(len+1));
    str[len] = '\0';
    return str;
}

void input_string(char *str) {
    printf("Enter string\n");
    scanf("%s", str);
}


/*
 *calculating h-index in citation
 *http://www.careercup.com/question?id=14585874
 *https://en.wikipedia.org/wiki/H-index
 *
 *Example : 
 *Papers(idx)       1   2  3  4  5
 *Citations(Cit[])  10  8  5  4  3
 *
 *we have to find largest i such that ith paper has i citation
 *
 *case 1 : when the citation array is sorted in non-increasing order
 *
 *run a binsearh and find our the element such for which index i of citation array is greater or equal to citation 

 case 2 : when the citation array is unsorted
algo: 
1. build a min heap of the array in O(n) time
2. swap the first element with last, heapify remaining elements and check if index of last element > the number 
if yes then return that no ( this will be desired h index)
else
repeat step 2 with remaining elements, till the time you get index of last element < number. when found return the number as 
desired h index

 */

int citation(int *A, int l, int h) {

    int mid, h_idx;

    if(l>=h)
	return l;

    mid = (l+h)/2;

    if(A[mid]>mid)
	h_idx = citation(A, mid+1, h);
    else if(A[mid]< mid)
	h_idx = citation(A, l, mid-1);
    else 
	h_idx = mid+1; 

    return h_idx;

}

int min_element_rotated_sorted(int *A, int l, int h) {

    int mid, res;

    mid =  l + (h-l)/2;

    /*if(A[l] <= A[mid] && A[mid] < A[h])*/
	/*return A[l];*/

    if(l>=mid)
	return A[h];
	

    if(A[l] < A[mid] && A[mid] > A[h])
	res = min_element_rotated_sorted(A, mid+1, h);
    else if(A[l] > A[mid] && A[mid] < A[h])
	res = min_element_rotated_sorted(A, l, mid);

    return res;
}

int occurence(int *A, int l, int h, int num) {

    int res, mid;

    if(l>=h)
	return l;

    mid = (l+h)/2;
    if(A[mid] < num)
	res = occurence(A, mid+1, h, num);
    else 
	res = occurence(A, l, mid, num);
    return res;
}

/*
 *http://www.careercup.com/question?id=5751441480220672
 * In an array, find two numbers so that
 * a) the difference between them is 1
 * b) most number of elements in the array lie between them.
 *  
 */


 float search(float *A, int l, int h, float num) {

     int res, mid;
     if(l>=h)
	 return l;

     mid = (l+h)/2;
     if(A[mid] < num)
	 res = search(A, mid+1, h, num);
     else
	 res = search(A, l , mid, num);

	     return res;

 }

 void range(float *A, int n) {

     int i;
     float count = LONG_MIN;

     for(i=0;i<n-1;i++){
	 if(search(A, i+1, n, A[i]+1) - i > count)
	     count = A[i];
     }

 }

/*
 *leetcode problem 268
 *https://leetcode.com/problems/missing-number/
 */

int missing_number(int *A, int low, int high) {

    int mid;
    int res;

    if(low >= high)
	return low;

    mid = low + (high-low)/2;

    // if the diff between no and its index at low is equal to mid , then the missing number lies in the right half of array
    if((A[low]-low) == (A[mid]-mid)){
	res = missing_number(A, mid+1, high);
    } else { // else no lies on the left half
	res = missing_number(A, low, mid);
    }
    return res;
}


/*
 *rotate the array n times
  http://www.careercup.com/question?id=5695475640434688
  TBD
*/


int num_of_occurences_util(int *A, int low, int high, int num) {

    int mid, res;

    if(low>=high)
	return low;

    mid = low+(high-low)/2;


    if(A[mid] < num)
	res = num_of_occurences_util(A, mid+1, high, num);
    else if (A[mid] >= num)
	res = num_of_occurences_util(A, low, mid, num);

    return res;
}

void num_of_occurences(int *A, int len) {

    int curr_idx, prev_idx;

    /*pointer to the end of the array*/
    curr_idx = len-1;
    prev_idx = curr_idx;

    while(curr_idx>=0){
	curr_idx = num_of_occurences_util(A, 0, curr_idx, A[curr_idx]);
	printf("Number[%d] Frequency[%d]\n", A[curr_idx], prev_idx-curr_idx+1);
	prev_idx = curr_idx - 1;
	curr_idx--;
    }
}

int main() {
    char c;
    int choice, n, num;
    int  *A;
    float Arr[6] = {12.3, 12.5, 12.9, 13.3, 13.7, 14.9};
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- citation problem\n");
	printf("2 -- Find the minimum element(point of rotation) in rotated sorted array\n");
	printf("3 -- Find the number of occurances of a given number in a sorted array\n");
	printf("4 -- Max range in an array\n");
	printf("5 -- Find the missing number\n");
	printf("6 -- count the number of occurrences of an element in a sorted array\n");


	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){

	    case 1: 
		printf("Enter length of Citation array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		printf("h_index: %d\n", citation(A, 0, n-1));
		free(A);
		break;

	    case 2:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		printf("Minimum element: %d\n", min_element_rotated_sorted(A, 0, n-1));
		break;

	    case 3:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		printf("Enter the number\n");
		scanf("%d", &num);
		printf("Index: %d\n", occurence(A, 0, n-1, num));
		break;

	    case 4:
		range(Arr, 6);
		break;

	    case 5: 
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		printf("Missing Number: %d\n", A[missing_number(A, 0, n-1)]-1);
		free(A);
		break;

	    case 6:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		num_of_occurences(A, n);
		break;

	    default:
		break;

	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
