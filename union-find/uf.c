#include "../utils.h"

/*initilize the union-find data structure*/
UF* uf_init(int total_obj ) {

    UF *uf = NULL;
    uf = (UF*)malloc(sizeof(UF));
    if(!uf)
        return NULL;

    uf->total_obj = total_obj;
    uf->parent = (int*)calloc(sizeof(int), total_obj);
    uf->size = (int*)calloc(sizeof(int), total_obj);

    if (!uf->uf_size  || !uf_parent)
        return NULL;

    /*initially each object in a set is its own root*/
    for(i=0;i<total_obj;i++){
        uf->parent[i] = i;
    }

    /*initially size of each subset is 1, since there is just one element(root) present in subset*/
    for(i=0;i<total_obj;i++){
        uf->parent[i] = 1;
    }

    return uf;
}

void uf_free(UF *uf) {

    if(uf) {
        uf->total_obj = 0;
        free(uf->uf_parent);
        uf->uf_parent = NULL;
        free(uf->uf_size)
        uf->uf_size = NULL;

        // free the structure now
        free(uf);
        uf = NULL;
    }
}

int get_root(UF *uf, int obj){

    if(!uf && !uf->parent && !uf->size)
        return -1;

    //loop till the time we dont find the root: Any object who is parent of itself is a root
    while(uf->parent[obj] != obj){
        obj = uf->parent[obj];
    }
    
    return obj
}

void uf_union(UF* uf, int obj1, int obj2) {

    int root1, root2;
/*
 *logic:  
 *    1. get root of obj1
 *    2. get root of obj2
 *    3. attach the  root of smaller sized subset  to the root of larger sized subset
 */

    root1 = get_root(uf, obj1);
    root2 = get_root(uf, obj2);
    if(uf->size[root1] <= uf->siz[root2]){
        uf->parent[root1] = root2;
        uf->size[root2] += uf->parent[root1]; 

    }else{
        uf->parent[root2] = root1;
        uf->size[root1] += uf->parent[root2]; 
    }
}

/*
 *returns:
 *1 -> if objects are connected
 *0 -> if ojects are connected
 *-1 -> invalid input
 */

int connected(UF* uf, int obj1, int obj2){

    int root1, root2;

    if(!uf || obj1 < 0 || obj2 < 0)
        return -1;

    root1 = get_root(uf, obj1);
    root2 = get_root(uf, obj2);

    if(root1==root2)
        return 1;
    else
        return 0;

}

void uf_print(UF *uf) {

    int i;
    if(!uf)
        return;
    printf("OBJ     PARENT\n");
    for(i=0;i<uf->size;i++){
        printf("%d\t\t%d", i, uf->parent[i]); 
    }

}
