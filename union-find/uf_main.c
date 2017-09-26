/*************************************************************************************
  CONCEPTS
https://www.youtube.com/watch?v=0jNmHPfA_yE
https://www.youtube.com/watch?v=VHRhJWacxis
https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
 **************************************************************************************/
#include "union_find.h"
#include "../utils.h"


int main() {
    int choice, n, obj1, obj2;
    UF *uf = NULL;

    do {

        printf("MENU OPTIONS\n");
        printf("1 -- create a union-find structure\n");
        printf("2 -- union\n");
        printf("3 -- find\n");
        printf("4 -- connected\n");

        printf("Enter your choice\n");
        scanf("%d",&choice);
        switch(choice){

            case 1: 
                printf("Enter no of elements(objects)\n");
                scanf("%d", &n);
                uf = uf_init(n);

                break;
            case 2:
                printf("Enter first object\n");
                scanf("%d", &obj1);
                printf("Enter second object\n");
                scanf("%d", &obj2);
                uf_union(uf, obj1, obj2);
                break;

            case 3:
                printf("Enter object\n");
                scanf("%d", &obj1);
                printf("root=%d\n", uf_find(uf, obj1);
                break;

            default:
                printf("Invalid option\n");
                break;
        }
        printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

 
