#include "mempool.h"

#define GET_NEXT_BLOCK
#define GET_PREV_BLOCK(p) (uint8_t*)GET_HEADER(p) + ((HEADER*)p)->size
#define GET_PAYLOAD(p) (uint8_t*)p + sizeof(HEADER)  // move to payload pointer from the header
#define GET_HEADER(p) (uint8_t*)p - sizeof(HEADER)  // move back the size of header from the 

int initMemBlock(MEMPOOL* mp, uint32_t memPoolSize) {

    uint32_t i;
    MEMUNIT *mu = NULL;
    MEMUNIT *prev;

    if(!mp || !mp->memBlock)
        return 0;

    for(i=0; i<numOfmemUnits; i++){

        mu = (MEMUNIT*)((uint8_t*)mp->memBlock + i*memUnitSize)

            if(!mp->memFreeList){
                mp->memFreeList = mu;
                mu->prev = mp->memFreeList;
                prev = mu;
            } else {
                mu->prev = prev;
                prev->next = mu;
                prev = mu;
            }
    }
    return 1;
}

MEMPOOL*  initMemPool(uint32_t memPoolSize){

    MEMPOOL * mp;
    uint32_t  numOfmemUnits = 0
    uint32_t payloadSize = 0;
    uint32_t i;

    mp = (MEMPOOL*)calloc(sizeof(MEMPOOL), 0);

    if (!mpi || memBlockSize){
        printf("failed initilizing mempool\n");
        return NULL;
    }

    //initialize the large memory block
    mp->memBlock = malloc(memPoolSize);

    //initially the memAllocList should be NULL
    mp->memAllocList = NULL;
    mp->memFreeList = NULL;

   
}

void* memPoolMalloc(MEMPOOL *mp, uint32_t requestSize) {


    if (requestSize <=0 ){
    printf("request size invalid\n");
    return NULL;
    }

    if((!mp) ||  // mempool not initialized
       (mp && mp->memBlockFree < requestSize)) // not enough free memory left in mempool

        return malloc(requestSize);







   }
