//http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/
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
 
int minCostPath(int **a, int r, int c) {

    int sum;

    if(r < 0 || c < 0)
        return INT_MAX;

    if(r==0 && c==0){
        return a[r][c];
    }
    /*selectMin(a, r, c, &m_row, &m_col);*/
    sum = a[r][c] + min(minCostPath(a, r-1, c), minCostPath(a, r, c-1), minCostPath(a, r-1, c-1));

    return sum;
}

int main(){

    int **a, i,j, rows, cols;
    int idx1, idx2;
    printf ("enter no of rows\n");
    scanf("%d", &rows);

    printf ("enter no of cols\n");
    scanf("%d", &cols);

    a = (int**)malloc(sizeof(int*)*rows);

    for(i=0;i<rows;i++) {
    a[i] = (int*)malloc(sizeof(int)*cols);
    }

    printf ("enter elements\n");
    for(i=0;i<rows;i++){
        for (j=0;j<cols;j++) {
        scanf("%d", &a[i][j]);
        }
    }

    for(i=0;i<rows;i++){
        for (j=0;j<cols;j++) {
        printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("Enter the indices to find min cost to\n");
    scanf("%d%d", &idx1, &idx2);
    printf("Min Cost Path = %d", minCostPath(a, idx1, idx2));

    return 0;
}
