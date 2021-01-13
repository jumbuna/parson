#ifndef _PARSER_H
#define _PARSER_H
#include "../include/list.h"
#include "../include/lexer.h"

typedef struct Json {
    list_t *values;
} json_t;

#ifdef _PARSER_C
    json_t *jsonParse();
#else
    extern json_t *jsonParse();
#endif

#endif /* _PARSER_H */