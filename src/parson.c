#include <stdio.h>
#include "../include/parson.h"
#include <stdlib.h>
#include <string.h>

struct Json *parsonParse(char *filename) {
    Istream = fopen(filename, "r");
    if(Istream == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }
    return jsonParse();
}

void parsonFree(struct Json *json) {

}

void *parsonGetByKey(struct Json *json, char *key) {
    if(json != NULL) {
        node_t *temp = json->values->head;
        while(temp != NULL) {
            if(strcmp(temp->key, key) == 0) return temp->val;
            temp = temp->next;
        }
    }
    return NULL; 
}

_Bool parsonContains(struct  Json *, char *);

void parsonPrettify(struct Json * _Nonnull json ) {
    static int padding = 0;
    node_t *temp = json->values->head;
    printf("%*s%c\n", padding, "", '{');
    while (temp != NULL) {
        printf("'%s' : '%s'", temp->key, (char*) temp->val->val);
        temp->next == NULL ? printf("\n") : printf(",\n");
        temp = temp->next;
    }
    printf("}");
}
