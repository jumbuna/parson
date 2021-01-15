#include <stdlib.h>

typedef struct Block {
    void *mem;
    struct Block *next;
} block_t;

typedef struct Allocator {
    block_t *head;
    void **freeList;
    size_t width;
    size_t len;
    size_t used;
} allocator_t;

allocator_t *AllocatorCreate(size_t, size_t);

void AllocatorDestroy(allocator_t *);

void *AllocatorAllocate(allocator_t *);

void AllocatorDeallocate(allocator_t *, void *);

block_t *BlockCreate(size_t, block_t *);

void BlockDestroy(block_t *);

// void *FreeListPop(void **);

// void FreeListPush(void *);