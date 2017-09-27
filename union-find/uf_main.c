/*************************************************************************************
  CONCEPTS
https://www.youtube.com/watch?v=0jNmHPfA_yE
https://www.youtube.com/watch?v=VHRhJWacxis
https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
 **************************************************************************************/
#include "uf.h"
#include "../utils.h"


int main() {
    int choice, n, obj1, obj2;
    char c;
    UF *uf = NULL;

    do {

        printf("MENU OPTIONS\n");
        printf("1 -- create a union-find structure\n");
        printf("2 -- union\n");
        printf("3 -- find root\n");//find the root of the object
        printf("4 -- connected\n"); // check if two objects are in the same subset(directly/indirectly connected)

        printf("Enter your choice\n");
        scanf("%d",&choice);
        switch(choice){

            case 1: 
                printf("Enter no of elements(objects)\n");
                scanf("%d", &n);
                uf = uf_init(n);
                uf_print(uf);

                break;
            case 2:
                printf("Enter first  and second object\n");
                scanf("%d", &obj1);
                /*printf("Enter second object\n");*/
                scanf("%d", &obj2);
                uf_union(uf, obj1, obj2);
                uf_print(uf);
                break;

            case 3:
                printf("Enter object\n");
                scanf("%d", &obj1);
                printf("root=%d\n", get_root(uf, obj1));
                break;

            case 4:
                printf("Enter first and second object\n");
                scanf("%d", &obj1);
                /*printf("Enter second object\n");*/
                scanf("%d", &obj2);
                printf("Connected:%d\n", uf_connected(uf, obj1, obj2));
                break;


            default:
                printf("Invalid option\n");
                break;
        }
        printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

 
