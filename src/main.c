#include "../include/lexer.h"
#include <stdio.h>
#include "../include/parson.h"

int main(int argc, char **argv) {
    json_t *j =  parsonParse(argv[1]);
    char *k = NULL;
    size_t kl = 0;
    while(1) {
        printf(">>> ");
        int c = getline(&k, &kl, stdin);
        k[c-1] = 0;
        value_t *v = parsonGetByKey(j, k);
        switch(v->type) {
            case ARRAY : {
                printf("%s : [", k);
                node_t *n = ((list_t *)v->val)->head;
                while(n != NULL) {
                    printf("%s", (char*) n->val->val);
                    n = n->next;
                    if(n != NULL) printf(", ");
                }
                printf("]\n");
                break;
            }
            default: printf("%s : %s\n", k, (char*) v->val);
        }
    }
}