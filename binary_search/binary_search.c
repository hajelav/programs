#include "../utils.h"

void print_1Darray_index(int *A, int i, int j){
int k;
    for(k=i;k<=j;k++){
	printf("%d ", A[k]);
    } 
    printf("\n");
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

int binary_search(int *A, int low, int high, int key) {

    int mid, res;

    if(low>high)
	return -1;

    mid = low + ((high-low)>>1);

    if(A[mid] == key)
	return mid;

    if(key < A[mid])
	res = binary_search(A, low, mid-1, key);
    else if(key > A[mid])
	res = binary_search(A, mid+1, high, key);

    return res;
}

/*get the index of point of rotation*/
/*
 *int get_pivot_rotated_sorted(int *A, int l, int h) {
 *
 *    int mid, res;
 *
 *    mid =  l + (h-l)/2;
 *
 *    if(l>=h)
 *        return l;
 *
 *    if(A[l] <= A[mid] && A[mid] > A[h])
 *        res = get_pivot_rotated_sorted(A, mid+1, h);
 *    else if(A[l] > A[mid] && A[mid] < A[h])
 *        res = get_pivot_rotated_sorted(A, l, mid);
 *    else if(A[l] <= A[mid] && A[mid] <= A[h]) //handle duplicates
 *        return l;
 *
 *    return res;
 *}
 */

int get_pivot_rotated_sorted(int *A, int l, int h) {

    int mid, res;

    mid =  l + (h-l)/2;

    if(l>=h)
	return l;

    if(A[l] < A[mid])
	res = get_pivot_rotated_sorted(A, mid, h);
    else if (A[l] > A[mid]) 
	res = get_pivot_rotated_sorted(A, l, mid);
    else
	res = get_pivot_rotated_sorted(A, mid+1, h);


    return res;
}

/*search an element in rotated sorted array, with length as len*/
int search_rotated_sorted(int *A, int len, int key) {

    int pivot_idx; //index of pivot
    int idx;

    if(!A || len < 1)
	return -1;

    /*first find out the pivot of roation in the array, the functions returns 
     * the index of last element in array if there is no pivot found*/

    pivot_idx = get_pivot_rotated_sorted(A, 0, len-1);

    printf("Pivot index : %d\n", pivot_idx);

    if(pivot_idx < len-1) {
	//the array is rotated, now just search the element in two sorted arrays
	if((idx = binary_search(A, 0, pivot_idx-1, key)) < 0)
	    return binary_search(A, pivot_idx, len-1, key);
	else 
	    return idx;
    } else {
	/*the array is not rotated, do a bin search in the entire array*/
	return binary_search(A, 0, len-1, key);
    }
} 

/*linkedin*/
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
 Given a sorted array of size n. Each element in an array is unique and lies from 1 to n+1. How do you find the missing element

 For example,
 Given nums = [0, 1, 3] return 2.
 */

int missing_number_old(int *A, int low, int high) {

    int mid;
    int res;

    if(low >= high)
	return low;

    mid = low + (high-low)/2;

    // if the diff between no and its index at low is equal to mid , then the missing number lies in the right half of array
    if((A[low]-low) == (A[mid]-mid) && (low!=mid)){
	res = missing_number_old(A, mid, high);
    } else { // else no lies on the left half
	res = missing_number_old(A, low, mid);
    }
    return res;
}

int missing_number(int *A, int low, int high) {

    int mid;
    int res;

    if(low >= high)
	return low;

    mid = low + (high-low)/2;

    if (low == mid)
        return low;


    // if the diff between no and its index at low is equal to mid , then the missing number lies in the right half of array
    if(mid < A[mid]){
	res = missing_number(A, low , mid-1);
    } else { // else no lies on the left half
	res = missing_number(A, mid, high);
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

int greater_number(int *A, int low, int high, int target){

    int mid, res;

    if(low>=high)
	return low;

    mid = low+(high-low)/2;


    if(A[mid] <= target)
	res = greater_number(A, mid+1, high, target);
    else if (A[mid] > target)
	res = greater_number(A, low, mid, target);

    return res;
}

int main() {
    char c;
    int choice, n, num;
    int res;
    int  *A;
    float Arr[6] = {12.3, 12.5, 12.9, 13.3, 13.7, 14.9};
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- citation problem\n");
	printf("2 -- Find the point of rotation(pivot) in rotated sorted array\n");
	printf("3 -- Find the number of occurances of a given number in a sorted array\n");
	printf("4 -- Max range in an array\n");
	printf("5 -- Find the missing number\n");
	printf("6 -- count the number of occurrences of all elements in a sorted array\n");
	printf("7 -- search an element in rotated sorted array\n");
	printf("8 -- find the first element in an array that is greater than the target in a sorted array\n");


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
		res = get_pivot_rotated_sorted(A, 0, n-1);
		printf("index of rotation(pivot): %d\n", res);
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
		printf("Missing Number: %d\n", A[missing_number(A, 0, n-1)]+1);
		free(A);
		break;

	    case 6:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		num_of_occurences(A, n);
		break;

	    case 7:
		printf("Enter the length of rotated sorted array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		printf("Enter the element to be searched\n");
		scanf("%d", &num);
		printf("key found at index : %d\n", search_rotated_sorted(A, n, num));
		/*printf("key found : %s\n", binary_search(A, 0, n, num)>=0?"yes":"no");*/
		break;

	    case 8:
		printf("Enter the length of array\n");
		scanf("%d", &n);
		A = create_1Darray(n); 
		input_array(A, n);
		printf("Enter the target number\n");
		scanf("%d", &num);
		if(num < A[n-1])
		printf("index of number greater than %d : %d\n", num, greater_number(A, 0, n-1, num));
		else
		printf("greater number does not exist\n");

		break;
		

	    default:
		break;

	}
	printf("\n");
    }while((c=getchar())!='q'); 
    return 0;
}
