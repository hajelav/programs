

//http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
//gcc  minCostPath_recursive.c -Wall -o minCostPath_recursive

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

 
int LIS(int *a, int elem) {

    int *S, i, j;
    int max = 1;

    S = (int*)malloc(sizeof(int)*elem);

    //base case  
    S[0] = max;

    for (i=1;i<elem;i++){
        for(j=0;j<i;j++) {
            if(a[j] > a[i]){
                if(S[j]+1 > max){
                    max = S[j]+1;
                } 
            } 
        }
        S[i] = max;
        max = 1;
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
    return max;
}

int main(){

    int *a,i, elem;

    printf("Enter no of elements\n");
    scanf("%d", &elem);

    a = (int*)malloc(sizeof(int)*elem);
    printf("Enter elements\n");

    for(i=0;i<elem;i++){
        scanf("%d", &a[i]);
    }

    printf("Longest Decresing Subsequence=%d\n", LIS(a, elem));

    return 0;
}
