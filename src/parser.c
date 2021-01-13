#include "../include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/uthash.h"
#include "../include/list.h"


void *keyValPairs(), keyValPair(), *key(), *val(), *array();

void printer(char *n, void *v) {
    printf("%s => %p\n", n, v);
}

/**
 *
 */
char *json() {
    list_t *l = NULL;
    if(getNextToken() == Tok_BraceOpen) {
        do {
            advance();
            l = keyValPairs();
            if(getNextToken() != Tok_BraceClose) {
                printf("Missing closing }");
                exit(1);
            }
            advance();
        } while(getNextToken() == Tok_BraceOpen);
    } else {
        printf("Missing opening { \n");
        exit(1);
    }
    ListForEach(l, printer);
    return 0;
}

void *keyValPairs() {
    list_t *list = ListCreate();
    char *k;
    void *v;
    keyValPair(&k, &v);
    ListInsertBack(list, k, v);
    while (getNextToken() == Tok_End) {
        advance();
        keyValPair(&k, &v);
        ListInsertBack(list, k, v);
    }
    return list;
}

void keyValPair(char **k, void **v) {
    *k = key();
    if(getNextToken() != Tok_Separator) {
        printf("Expected `:` \n");
        exit(1);
    }
    advance();
    *v = val();
}

void  *key() {
    if(getNextToken() != Tok_Key) {
        printf("Unexpected character %c on line %d\n", LastChar, CurrentLine);
        exit(1);
    }
    return strdup(buffer);
}

void *val() {
    switch(getNextToken()) {
        case Tok_String:
        case Tok_Bool:
        case Tok_Number: return strdup(buffer);
        case Tok_ParenOpen: return array();
        case Tok_BraceOpen: return json();
        default: printf("Unexpected `%c` on line %d\n", LastChar, CurrentLine);exit(1);
    }
}


void *array() {
    list_t *l = ListCreate();
    int i = 0;
    advance();
    while (getNextToken() != Tok_ParenClose) {
        ListInsertBack(l, 0, val());
        advance();
        if(getNextToken() == Tok_End) {
            advance();
        } else {
            ungetc(1, Istream);
        }
    }
    return l;
}