//http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
//gcc  minCostPath_recursive.c -Wall -o minCostPath_recursive

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int x, int y, int z)
{
       if (x < y)
                 return (x < z)? x : z;
          else
                    return (y < z)? y : z;
}
 
int maxSumIncresingSeqDynamic(int *a, int elem) {

    int *S, i, j;
    int max = 0;

    S = (int*)malloc(sizeof(int)*elem);

    //base case  
    S[0] = a[0];

    for (i=1;i<elem;i++){
        for(j=0;j<i;j++) {
            if(a[j] < a[i]){
                if(a[i]+S[j] > max){
                    max = a[i]+S[j];
                } 
            } 
        }
        S[i] = max;
        max =0;
    }
    for(i=0;i<elem;i++){
        printf("%d ", S[i]);
    }

    //for the solution, find the max of the array S
    return 0;
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

    /*for(i=0;i<elem;i++){*/
        /*printf("%d", a[i]);*/
    /*}*/

    printf("Max Sum Incresing Sequence=%d\n", maxSumIncresingSeqDynamic(a, elem));

    return 0;
}
