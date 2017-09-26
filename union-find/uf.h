#include "../utils.h"

/*
 *DEFINITION oF UNION-FIND DATA STRUCTURE:
 *it has a set of objects(chars in this implementation). the basic idea of representing a set of objects
 *is by an array , where the index of array is tha actual object while array[index] represents the relationship 
 *between objects. In this implementation array[index] represents "leader" relationships. See youtube videos(in union_find_main.c) for more explaination.
 *
 * NOTE : This implementation assumes that all the objects are represented by numbers starting from 0
 */

//data structure for union-find 
typedef struct _uf {
    int *parent; // each element in the array represent a subset in a union-find and the index is represent by objects itself
    int *size; // size of each subset
    int total_obj; // total number of objects to be grouped into subsets
}UF;

UF* uf_init(int total_obj);
void uf_union(int obj1, int obj2); //combine the two subsets
int uf_find(UF *uf); // find the root of the subset
void uf_free(UF *uf)
int connected(UF* uf, int obj1, int obj2); // check if obj1 and obj2 belong to a the same subset(connected)
void uf_print(UF *uf);


