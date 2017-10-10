#include "../utils.h"

typedef struct header {
    struct header *prev;
    struct header *next;
    uint32_t size;
    uint32_t used:1;
}HEADER;

//data structure for a memory pool
typedef struct _memPool {
    uint32_t memBlockSize;  // total size of the mempool, ie the block of memory to be requested from the heap of OS
    HEADER *memFreeList;   // list of free mem units
    HEADER *memAllocList;  // list of allocatted mem units
}MEMPOOL;

void initMemPool(MEMPOOL *mp, uint32_t memBlockSize);
void* memPoolMalloc(MEMPOOL *mp, uint32_t requestSize);
void memPoolFree();





