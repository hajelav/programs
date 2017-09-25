#include "../utils.h"

//data structure for union-find 
typedef struct _uf {
    int *uf; // each element in the array represent a subset in a union-find
    int *size;

}UF;

DF* init_uf(size);
void uf_union(int obj1, int obj2); //combine the two subsets
int uf_find(UF *uf);





