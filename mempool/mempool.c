#include "mempool.h"

typedef struct _memUnit  {
    struct _memUnit *prev;
    struct _memUnit *next;
}MEMUNIT;

//data structure for a memory pool
typedef struct _memPool {
    uint32_t memBlockSize;  // total size of the mempool, ie the block of memory to be requested from the heap of OS
    uint32_t memUnitSize;   // size of each mem unit inside the mempool. internally mem block layout is defined by mem units
    MEMUNIT *memFreeList;   // list of free mem units
    MEMUNIT *memAllocList;  // list of allocatted mem units
    uint32_t memBlockUsed;  // total memory  used 
    uint32_t memBlockFree;  // total memory free
}MEMPOOL;
void initMemPool(MEMPOOL *mp, uint32_t memUnitSize, uint32_t memBlockSize){




}
