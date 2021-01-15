#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list_t *ListCreate(allocator_t *alloc) {
    list_t *new = calloc(1, sizeof(list_t));
    new->allocator = alloc;
    return new;
}

void ListInsertBack(list_t *list, char *key, void *val) {
    if(list->length == 0) {
        list->tail = list->head = AllocatorAllocate(list->allocator);
    } else {
        list->tail->next = AllocatorAllocate(list->allocator);
        list->tail = list->tail->next;
    }
    list->tail->next = NULL;
    list->tail->key = key;
    list->tail->val = val;
    list->length++;
}

void ListForEach(list_t *list, void (*fun) (char *key, void *val)) {
    if(list->length == 0) return;
    node_t *temp = list->head;
    while(temp != NULL) {
        fun(temp->key, temp->val->val);
        temp = temp->next;
    }
}

void ListDestroy(list_t *list) {
    AllocatorDestroy(list->allocator);
    free(list);
}