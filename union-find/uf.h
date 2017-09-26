#include "../utils.h"

/*
 *DEFINITION oF UNION-FIND DATA STRUCTURE:
 *it has a set of objects(chars in this implementation). the basic idea of representing a set of objects
 *is by an array , where the index of array is tha actual object while array[index] represents the relationship 
 *between objects. In this implementation array[index] represents "leader" relationships. See youtube videos(in union_find_main.c) for more explaination.
 *
 */

//data structure for union-find 
typedef struct _uf {
    int *uf_leader; // each element in the array represent a subset in a union-find and the index is represent by objects itself
    int *uf_size; // size of each subset
    int  total_obj; // total number of objects to be grouped into subsets

}UF;

UF* uf_init(int total_obj);
void uf_union(int obj1, int obj2); //combine the two subsets
int uf_find(UF *uf);
void uf_free(UF *uf)


