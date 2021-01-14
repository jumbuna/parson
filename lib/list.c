#include "list.h"
#include <stdio.h>
#include <stdlib.h>

node_t *NodeCreate() {
    node_t *new = malloc(sizeof(node_t));
    return new;
}

void NodeDestroy(node_t *node) {
    free(node);
}

list_t *ListCreate() {
    return calloc(1, sizeof(list_t));

}

// void ListInsertFront(list_t *, void *);

void ListInsertBack(list_t *list, char *key, void *val) {
    if(list->length == 0) {
        list->tail = list->head = NodeCreate();
    } else {
        list->tail->next = NodeCreate();
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