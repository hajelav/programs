#include "mempool.h"

typedef struct _memUnit  {
    struct _memUnit *prev;
    struct _memUnit *next;
}MEMUNIT;

//data structure for a memory pool
typedef struct _memPool {
    uint32_t memBlockSize;  // total size of the mempool, ie the block of memory to be requested from the heap of OS
    uint32_t memUnitSize;   // size of each mem unit inside the mempool. internally mem block layout is defined by mem units
    void*    memBlock;
    MEMUNIT *memFreeList;   // list of free mem units
    MEMUNIT *memAllocList;  // list of allocatted mem units
    uint32_t memBlockUsed;  // total memory  used 
    uint32_t memBlockFree;  // total memory free
}MEMPOOL;

void initMemBlock(MEMPOOL* mp, uint32_t numOfmemUnits, uint32_t memUnitSize) {

    uint32_t i;
    MEMUNIT *mu = NULL;
    MEMUNIT *prev;

    if(!mp || !mp->memBlock || numOfmemUnits <=0)
        return;

    

    for(i=0; i<numOfmemUnits; i++){

        mu = (MEMUNIT*)((uint8_t*)mp->memBlock + i*memUnitSize)
            if(!mp->memFreeList){

                

            }
    }
}

MEMPOOL*  initMemPool(uint32_t memUnitSize, uint32_t memBlockSize){

    MEMPOOL * mp;
    uint32_t  numOfmemUnits = 0
    uint32_t payloadSize = 0;
    uint32_t i;

    mp = (MEMPOOL*)calloc(sizeof(MEMPOOL), 0);
    if (!mpi || memUnitSize || memBlockSize){
        printf("failed initilizing mempool\n");
        return NULL;
    }

    if(memBlockSize < memUnitSize)
        printf("Block memory size cannot be less than memory unit size\n");

    //initialize the large memory block
    mp->memBlock = malloc(memBlockSize);

    // initialize the attributes
    mp->memBlockSize = memBlockSize;
    mp->memUnitSize = memUnitSize;
    
    //initially the memAllocList should be NULL
    mp->memAllocList = NULL;
    mp->memFreeList = NULL;

   // initially total memory used will be equal to 0
   mp->memBlockUsed = 0;

   //initially the total memory avaialable would be the combined total of all payloads in each free mem units
   
   numOfmemUnits =  (memBlockSize/memUnitSize)
   payloadSize = memUnitSize - (sizeof(MEMUNIT));

   mp->memBlockFree = memBlockSize - (numOfmemUnits*sizeof(MEMUNIT); 

   //cast the raw memory(memBlock) into memUnits
   initMemBlock(mp, numOfmemUnits);
   for(i=0; i<numOfmemUnits; i++){


   }
   


        

    
    
    











}
