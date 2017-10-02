#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>


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
}

int MIN(int a, int b) {

    return a>b?b:a;

}
int MAX(int a, int b) {

    return a>b?a:b;

}

int MOD(int x, int y) {
    return (x-y)>0?(x-y):(0-(x-y));
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
	    /*j++;*/
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

/*Inversion Count for an array indicates – how far (or close) the array is from being sorted. If array is already sorted then inversion count is 0. If array is sorted in reverse order that inversion count is the maximum. 
 * Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j Example:
 * The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
 *
 *
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

    int piv; //pivot

    if(low>=high)
	return;

    piv = partition(A, low, high);
    quicksort(A, low, piv-1);
    quicksort(A, piv+1, high);
}

/*
 *order statistics using quickselect method (O(n) time). this is also known as linear selection algorithm
 */
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
    piv = low; //as of now we take pivot as the first element in the array

   /*preprocess the array and swap the elements of 0th and piv */
    swap(A, low, piv); //only required when we choose random pivot

    /*
     *partition the array so that the random pivot is at its correct position in array
     *partition function places A[piv] to its correct position and returns its index
     */

    j = partition(A, low, high);
    /*if we are in luck to get the random pivot as the desired ith order stats then return it*/
    if(st == j){
    return A[j];
    }

    /*
     *if the pivot index(j) is greater than st(ith order statistic), then we need to recurse the     array , right of pivot ie, from j+1 to high and find st-j order stats  
     */
    if(st>j)
    ret = order_statistic(A, j+1, high, st);
    else 
    ret = order_statistic(A, low, j-1, st);

    return ret;
}

/*
 *note : this only works when size of both arrays are same
if number of elements in the array is even(n%2 == 0) , the output will be 
(median + 1)th index

 */

int median_sorted_arrays_same_size(int *A, int *B, int lA, int hA, int lB, int hB) {

   int midA, midB;
   int median;

   

   if(hA-lA == 1 || hB-lB == 1){
       //base case when both A and B have 2 elements
       return (MIN(MAX(A[lA], B[lB]), MIN(A[hA], B[hB])));
   }


   midA = (lA+hA)/2;
   midB = (lB+hB)/2;

   if(A[midA] < B[midB]){
       median = median_sorted_arrays(A, B, midA, hA, lB, midB);   
   } else if (A[midA] > B[midB]) {
       median = median_sorted_arrays(A, B, lA, midA, midB, hB);  
   } else {
       return A[midA];
   }
    return median;
}


int median_sorted_arrays_different_sizes(int *A, int *B, int lA, int hA, int lB, int hB) {

   int midA, midB;
   int median;


   if(hA-lA == 1 || hB-lB == 1){
       //base case when both A and B have 2 elements
       return (MIN(MAX(A[lA], B[lB]), MIN(A[hA], B[hB])));
   }


   midA = (lA+hA)/2;
   midB = (lB+hB)/2;

   if(A[midA] < B[midB]){
       median = median_sorted_arrays(A, B, midA, hA, lB, midB);   
   } else if (A[midA] > B[midB]) {
       median = median_sorted_arrays(A, B, lA, midA, midB, hB);  
   } else {
       return A[midA];
   }
    return median;
}

int _2sum(int *A, int i, int j, int sum) {

    //sort the array first
    mergesort(A, i, j);
    /*i =0, j = n;*/
    while(i!=j){
	if(A[i]+A[j] < sum)
	    i++;
	else if(A[i]+A[j] > sum)
	    j--;
	else
	    return 1;
    }
    return 0;
}

void _2sum_closest(int *A, int i, int j, int sum) {

    int closest_i, closest_j;
    int diff = INT_MAX;
    mergesort(A, i, j);

    while(i!=j){

	if(MOD(A[i]+A[j] ,sum) < diff){
	    diff = MOD(A[i]+A[j] ,sum);	
	    closest_i = i;
	    closest_j = j;
	}

	if(A[i]+A[j] < sum){
	    i++;
	}
	else if(A[i]+A[j] > sum)
	    j--;
	else
	   break; //exit from the loop if u find i and j which equals sum 
    }

    printf("Closest nos to sum %d: %d, %d\n", A[closest_i], A[closest_j], sum);

}

/*
 *leetcode problem 15
 *https://leetcode.com/problems/3sum/
 */

int _3sum(int *A, int l, int h, int sum) {

    int i;

    if(!A || ((h-l+1) < 3))
	return 0;
    //sort the array first
    mergesort(A, l, h);
    for(i=l; i < h-1; i++){
	if(_2sum(A, i+1, h, sum-A[i])) 
		return 1;
    }	
    return 0;
}

/*
 *leetcode problem 16
 *https://leetcode.com/problems/3sum-closest/
 */

void _3sum_closest_util(int *A, int i, int j, int sum, int orig_target_sum) {

    static int closest_i, closest_j;
    static int diff = INT_MAX;
    /*mergesort(A, i, j);*/

    while(i!=j){

	if(MOD(A[i]+A[j] ,sum) < diff){
	    diff = MOD(A[i]+A[j] ,sum);	
	    closest_i = i;
	    closest_j = j;
	    printf("Closest nos to sum %d: %d, %d, %d\n", orig_target_sum, orig_target_sum- sum, A[closest_i], A[closest_j]);
	}

	if(A[i]+A[j] < sum){
	    i++;
	}
	else if(A[i]+A[j] > sum)
	    j--;
	else
	   break; //exit from the loop if u find i and j which equals sum 
    }

}

void _3sum_closest(int *A, int l, int h, int target) {

    int i;

    if(!A || ((h-l+1) < 3))
	return;
    //sort the array first
    mergesort(A, l, h);
    for(i=l; i < h-1; i++){
	_3sum_closest_util(A, i+1, h, target-A[i], target);
    }	
}


/*
 *Examples of K-way external sorting using max-heap
 *
 *1.Determine the 10 most frequent words given a terabyte of strings.
 *sol : Assuming that you have only 1 GB of RAM and 1TB file is stored on disk
 *
 *1. divide the file into 1024 chunks of 1 GB
 *2. Copy the file into main memory and sort the words in lexicographical order.
 *3. Parse the sorted words and maintain the count of each word, ex: <1000> "the", <200> "boy" in decresing order
 *4. Do this procedure for each of 1024 1 GB chunk and write the data back to the disk.
 *5. Now maintain a Max-Heap of 1024 elements and do K-way external merge sorting
 *        5.1 delete the max element from the heap and replace it with the next element of that chunk which was just deleted.
 *        5.2 repeat this procedure K times to get 10 most frequent words in 1 TB file.
 *
 */


/*
 *http://www.careercup.com/question?id=4830599367884800
 given an array of random integers, we have to divide the array into two equal halves, so
 that the difference in their sum is minimum
 */


/* get of intergers from l to h */
int get_sum(int *A, int l, int h) {
    int i, sum = 0;
    for(i=l;i<h;i++){
	sum += A[l];
    }
    return sum;
}

int  divide_array(int *A, int l, int h) {

    int mid, sumL, sumR, diff;
    int min = INT_MAX;
    //we first sort the array
    mergesort(A, l, h);

    mid = (l+h)/2;
    sumL = get_sum(A, l, mid);
    sumR = get_sum(A, mid+1, h);
    while (h>=mid+1) {
	while(l<=mid){
	diff = h-l;

	min = (sumR-diff) - (sumL + diff);
	
	if(((sumL + diff) <= (sumR-diff))){
	    if (min< ((sumR-diff) - (sumL + diff)))
		min = (sumR-diff) - (sumL + diff);
	} else {
	    /*if (min< ((sum-diff) - (sumL + diff)))*/
		/*min = (sumR-diff) - (sumL + diff);*/


	} 


	}
    }
    //TBD
return 0;
}


int NthOfSortedArrays(){

    /* TBD */
    return 0;
}


/*
 *radix sorting
 *https://www.youtube.com/watch?v=m-2jU13HuBU
 *
 *Example: 
 *
 *sort the sequence COW, DOG, SEA, RUG, ROW, MOB, BOX, TAB, BAR, EAR
 *
 *STEP 1:  start from the rightmost char, and but the chars into the buckets( 0- 25 buckets from A, Z)
 *   BUCKET		STRINGS
 *    A: 		SEA
 *    B: 		MOB, TAB
 *    G:		DOG, RUG
 *    R:		BAR, EAR
 *    W:		COW, ROW
 *    X:		BOX
 *
 *STEP 2: Repeat the same process for the 2nd char from right
 *   BUCKET	STRINGS
 *   A:		TAB, BAR, EAR
 *   E:		SEA,
 *   O:		MOB, DOG, COW, ROW, BOX
 *   U:		RUG
 *
 *STEP 2: Repeat the same process for the 3rd char from right(continue this process till you reach the end)
 *   BUCKET	STRINGS
 *   B:		BAR, BOX
 *   E:		EAR
 *   C:		COW,
 *   D:		DOG
 *   M:		MOB
 *   R:		ROW, RUG
 *   S:		SEA
 *   T:		TAB
 *
 *   At the end you get the sorted order
 */

/*
 *http://www.careercup.com/question?id=14099679
 *tetris game logic (Google interview question)
 */


/*
 *leetcode problem 280
 *https://leetcode.com/problems/wiggle-sort/
 */

void wiggle_sort(int *A, int n) {

    int i = 1, flag = 1;
    int temp;
    if(!A || n<=0)
	return;

    while(i<n) {
	
	if((flag && A[i] >= A[i-1]) || (!flag && A[i] <= A[i-i])){
	    //swap i and j
	    temp = A[i];
	    A[i] = A[i-1];
	    A[i-1] = temp;
	}
	i++;
	flag = !flag;
    }

    print_1Darray(A, n);
}

/**
 * [LinkedIn] http://www.careercup.com/question?id=5689376707182592
 * @brief
 ** Three segments of lengths A, B, C form a triangle iff
 **
 **      A + B > C
 **      B + C > A
 **      A + C > B
 **
 ** e.g.
 **  6, 4, 5 can form a triangle
 ** 10, 2, 7 can't
 **
 ** Given a list of segments lengths algorithm should find at least one triplet of segments that form a triangle (if any).
 **
 ** Method should return an array of either:
 ** - 3 elements: segments that form a triangle (i.e. satisfy the condition above)
 ** - empty array if there are no such segments
 **/

int *get_triangle_sides(int *A, int len) {

    int *res, i, j;

    if(len < 3)
	return NULL;

    res = (int*)calloc(3, sizeof(int));

    if(!res)
	return NULL;

    //sort the array first
    mergesort(A, 0, len-1);
    /*print_1Darray(A, len);*/

    for(i=2;i<len;i++){

	if(A[i-2]+A[i-1] > A[i]){
	    res[0] = A[i-2];
	    res[1] = A[i-1];
	    res[2] = A[i];

	    return res;
	}
    }

    
    for(i=2;i<len;i++){
	for(j=0;j<i-1;j++){
	    if(A[j]+A[j+1] > A[i])
		printf(" %d %d %d\n", A[j], A[j+1], A[i]);
	}
    }

    return NULL;
}

/*
 *given an array of n points in the plane, and the problem is to find out the closest pair of points in the array
 *http://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/
 */
void closest_pair() {

}



int main() {
    char c;
    int choice, n, m, s;
    int *A, *B;
    int *triangle;
    int sum;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Mergesort in an array\n");
	printf("2 -- Counting inversions in an array(divide and conquer method)\n");
	printf("3 -- Quicksort\n");
	printf("4 -- ith order statistics\n");
	printf("5 -- Median of two sorted arrays(divide and conquer method[logn]) of equal length\n");
	printf("6 -- find 2 numbers whose sum is equal to a given target\n");
	printf("7 -- find 3 numbers whose sum is equal to a given target\n");
	printf("8 -- Divide it into two Equal(it is important) partitions\n");
	printf("9 -- Given two sorted arrays find the element which would be N-th in their merged and sorted combination.\n");
	printf("10 -- Maximum contigous subarray using divide and conquer(nlogn)\n");
	printf("11 --  find 2 numbers closest to a given sum\n");
	printf("12 --  find 3 numbers closest to a given sum\n");
	printf("13 --  wiggle sort(up down up down pattern)\n");
	printf("14 -- given an array of integers, find at least a triplet which forms segments of a triangle\n");
	printf("15 -- given n points on a 2D plane find the closest pair\n");
	printf("16 -- median of two sorted array of different sizes\n");

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
		print_1Darray(A, n);
		free(A);
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

	    case 5:
		printf("Enter no of elements in array1\n");
		scanf("%d", &m);
		A = create_1Darray(m);
		input_array(A, m);
		printf("Enter no of elements in array2\n");
		scanf("%d", &n);
		B = create_1Darray(n);
		input_array(B, n);
		printf("Median of two sorted arrays of same size: %d", median_sorted_arrays_same_size(A, B, 0, m-1, 0, n-1));
		free(A);
		free(B);
		break;

	    case 6:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Enter target sum\n");
		scanf("%d", &sum);

		printf("2 sum exists: %s\n", _2sum(A, 0, n-1, sum)?"Yes":"No");
		break;

	    case 7:

		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Enter target sum\n");
		scanf("%d", &sum);

		printf("3 sum exits: %s\n", _3sum(A, 0, n-1, sum)?"Yes":"No");
		break;

	    case 8:
		printf("Enter no of elements in array1\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Min sum : %d\n", divide_array(A, 0, n-1));
		break;

	    case 11:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Enter sum\n");
		scanf("%d", &sum);

		/*printf("2 sum exits: %s\n", _2sum(A, 0, n-1, sum)?"Yes":"No");*/
		_2sum_closest(A, 0, n-1, sum);
		break;
	    case 12:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		printf("Enter target sum\n");
		scanf("%d", &sum);

		/*printf("2 sum exits: %s\n", _2sum(A, 0, n-1, sum)?"Yes":"No");*/
		_3sum_closest(A, 0, n-1, sum);
		break;

	    case 13:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		wiggle_sort(A, n);
		break;

	    case 14:
		printf("Enter no of elements in array\n");
		scanf("%d", &n);
		A = create_1Darray(n);
		input_array(A, n);
		triangle = get_triangle_sides(A, n);

		if(triangle)
		printf("triplet : %d %d %d\n", triangle[0], triangle[1], triangle[2]);
		else 
		printf("triplet : NULL\n");
		break;

	    case 15:
		closest_pair();
		break;

            case 16:
		printf("Enter no of elements in array1\n");
		scanf("%d", &m);
		A = create_1Darray(m);
		input_array(A, m);
		printf("Enter no of elements in array2\n");
		scanf("%d", &n);
		B = create_1Darray(n);
		input_array(B, n);
		printf("Median of two sorted arrays of different sizez: %d", median_sorted_arrays_different_sizes(A, B, 0, m-1, 0, n-1));
		free(A);
		free(B);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

