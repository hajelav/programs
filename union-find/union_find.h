#include "../utils.h"

//data structure for union-find 
typedef struct _uf {
    int *uf_leader; // each element in the array represent a subset in a union-find
    int *uf_size; // size of each subset
    int  total_obj; // total number of objects to be grouped into subsets

}UF;

UF* uf_init(int total_obj);
void uf_union(int obj1, int obj2); //combine the two subsets
int uf_find(UF *uf);
void uf_free(UF *uf)





