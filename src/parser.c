#include "../include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _PARSER_C
#include "../include/parser.h"
#undef _PARSER_C


list_t *keyValPairs();
void keyValPair(), *key(), *val(), *array();

/**
 *
 */
json_t *jsonParse() {
    json_t *json = malloc(sizeof(json_t));
    if(getNextToken() == Tok_BraceOpen) {
        do {
            advance();
            json->values = keyValPairs();
            if(getNextToken() != Tok_BraceClose) {
                printf("Missing closing }");
                exit(1);
            }
            advance();
        } while(getNextToken() == Tok_BraceOpen);
    }
    return json;
}

list_t *keyValPairs() {
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
    value_t *val = malloc(sizeof(value_t));
    switch(getNextToken()) {
        case Tok_String: {
            val->type = STRING;
            val->val = strdup(buffer);
            return val;
        }
        case Tok_Bool: {
            val->type = KYWRD;
            val->val = strdup(buffer);
            return val;
        }
        case Tok_Number: {
            val->type = NUMBER;
            val->val = strdup(buffer);
            return val;
        }
        case Tok_ParenOpen: {
            val->type = ARRAY;
            val->val = array();
            return val;
        }
        case Tok_BraceOpen: {
            val->type = JSON;
            val->val = jsonParse();
            return val;
        }
        default: printf("Unexpefcted `%c` on line %d\n", LastChar, CurrentLine);exit(1);
    }
}

void *array() {
    list_t *l = ListCreate();
    int i = 0;
    advance();
    while (1) {
        ListInsertBack(l, 0, val());
        token t = getNextToken();
        if(t == Tok_End) {
            advance();
        } else if(t == Tok_ParenClose) {
            break;
        }
    }
    advance();
    return l;
}