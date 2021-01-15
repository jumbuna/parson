#include "allocator.h"
#include <stdlib.h>
#include <string.h>

allocator_t *AllocatorCreate(size_t width, size_t len) {
    allocator_t *new = calloc(1, sizeof(allocator_t));
    new->width = width >= sizeof(void*) ? width : sizeof(void*);
    new->len = len;
    new->used = len;
    return new;
}

void *AllocatorAllocate(allocator_t *alloc) {
    if(alloc->freeList != NULL) {
        void **temp = alloc->freeList;
        alloc->freeList = *temp;
        return (void*) temp;
    }
    if(alloc->len == alloc->used) {
        alloc->head = BlockCreate(alloc->len * alloc->width, alloc->head);
        alloc->used = 0;
    }
    return &((char*)alloc->head->mem)[alloc->width * alloc->used++];
}

void AllocatorDeallocate(allocator_t *alloc, void *del) {
    memset(del, 0, alloc->width);
    void **t = del;
    *t = alloc->freeList;
    alloc->freeList = t;
}

block_t *BlockCreate(size_t size, block_t *next) {
    block_t *new = malloc(sizeof(block_t));
    new->mem = malloc(size);
    new->next = next;
    return new;
}

void BlockDestroy(block_t *block) {
    if(block == NULL) return;
    BlockDestroy(block->next);
    free(block->mem);
    free(block);
}

void AllocatorDestroy(allocator_t *alloc) {
    BlockDestroy(alloc->head);
    free(alloc);
    
}