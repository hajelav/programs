#include "../utils.h"

/*initilize the union-find data structure*/
UF* uf_init(int total_obj ) {

    UF *uf = NULL;
    uf = (UF*)malloc(sizeof(UF));
    if(!uf)
        return NULL;

    uf->total_obj = total_obj;
    uf->uf_leader = (int*)calloc(sizeof(int), total_obj);
    uf->uf_size = (int*)calloc(sizeof(int), total_obj);

    if (!uf->uf_size  || !uf_leader)
        return NULL;

    return uf;
}

void uf_free(UF *uf) {

    if(uf) {
        uf->total_obj = 0;
        free(uf->uf_leader);
        uf->uf_leader = NULL;
        free(uf->uf_size)
        uf->uf_size = NULL;

        // free the structure now
        free(uf);
        uf = NULL;
    }
}

void uf_union(int obj1, int obj2){




}

