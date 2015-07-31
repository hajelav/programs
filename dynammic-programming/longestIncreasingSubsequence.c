
//http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
//gcc  minCostPath_recursive.c -Wall -o minCostPath_recursive

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int MAX(int a, int b) {
    return (a>b?a:b);
}

void init_array(int *arr, int n){
    int i;
    for(i=0;i<n;i++){
	arr[i] = 1;
    }
}


/*
 *https://www.youtube.com/watch?v=CE2b_-XfVDk&index=35&list=PLrmLmBdmIlpsHaNTPP_jHHDx_os9ItYXr
 */
int LIS(int *a, int elem) {

    int *S, i, j;
    int max;

    //create an auxillary array to store all the longest increasing subsequence array length at each index i
    S = (int*)malloc(sizeof(int)*elem);

    //initialize all LIS length to 1
    init_array(S, elem);

    for (i=1;i<elem;i++){
        for(j=0;j<i;j++) {
            if(a[j] < a[i]){
		S[i] = MAX(S[i], S[j]+1);
                } 
            } 
        }

    for(i=0;i<elem;i++){
        printf("%d ", S[i]);
    }

    //for the solution, find the max of the array S
    max = 0;
    for(i=0;i<elem;i++) {
        if(S[i] > max){
            max = S[i];
        }
    }

    free(S);
    return max;
}

/*
 *www.8bitavenue.com/2011/12/dynamic-programming-edit-distance/
 */

int min_edit_distance(int *X, int *Y, int m, int n) {

}
int main(){


    char c;
    int choice;
    int *a,i, elem;
    int *X, *Y;
    int m, n; //length of array1 and array2
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Longest Increasing subsequence(LIS)\t");
	printf("2 -- Longest Common subsequence(LCS)\t");
	printf("3 -- Edit distance\n");
	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter no of elements\n");
		scanf("%d", &elem);

		a = (int*)malloc(sizeof(int)*elem);
		printf("Enter elements\n");

		for(i=0;i<elem;i++){
		    scanf("%d", &a[i]);
		}
		printf("\nLongest Incresing Subsequence=%d\n", LIS(a, elem));
		free(a);
		break;

	    case 2:
		/*https://drive.google.com/drive/folders/0BxHuWRSn-ApxVVJXZFJKOXZ1eWs*/
		/*http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence*/
		break;

	    case 3:
		printf("Enter no of elements of array 1\n");
		scanf("%d", &m);
		X = (int*)malloc(sizeof(int)*m);

		printf("Enter elements\n");
		for(i=0;i<m;i++){
		    scanf("%d", &X[i]);
		}
		printf("Enter no of elements of array 2\n");
		scanf("%d", &n);
		Y = (int*)malloc(sizeof(int)*n);

		printf("Enter elements\n");
		for(i=0;i<n;i++){
		    scanf("%d", &Y[i]);
		}
		printf("\nMinimum edit distance=%d\n", min_edit_distance(X, Y, m, n));
		free(X);
		free(Y);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;

    return 0;
}
