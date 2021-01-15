#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "parson.h"

struct Json *parsonParse(char *filename) {
    Istream = fopen(filename, "r");
    if(Istream == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }
    return JsonParse();
}

void parsonFree(struct Json *json) {
    JsonFree(json);
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

static void parsonPrintNode(node_t *node, int padding) {
    if(node->val->type != JSON) {
        printf("%*s", padding, "");
    }
    
    if(node->key != NULL) {
        printf("\"%s\": ", node->key);
    }
    switch(node->val->type) {
        case STRING: {
            printf("\"%s\"", (char*) node->val->val);
            break;
        }
        case KYWRD:
        case NUMBER: {
            printf("%s", (char*) node->val->val);
            break;
        }
        case ARRAY: {
            printf("[\n");
            node_t *temp = ((list_t *) node->val->val)->head;
            while(temp != NULL) {
                parsonPrintNode(temp, padding+4);
                temp = temp->next;
                if(temp != NULL) {
                    printf(",");
                }
                printf("\n");
            } 
            printf("%*s]", padding, "");
            break;
        }
        case JSON: {
            parsonPrettify(node->val->val, padding);
            break;
        }
    }
}

void parsonPrettify(struct Json * _Nonnull json, int padding) {
    node_t *temp = json->values->head;
    printf("%*s%c\n", padding, "", '{');
    padding += 4;
    while (temp != NULL) {
        parsonPrintNode(temp, padding);
        if(temp->next != NULL) {
            printf(",");
        }
        if(temp->val->type != JSON) {
            printf("\n"); 
        }
        temp = temp->next;
    }
    padding -= 4;
    printf("%*s}\n", padding, "");
}
