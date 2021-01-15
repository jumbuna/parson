#ifndef _PARSER_H
#define _PARSER_H
#include "list.h"
#include "lexer.h"

typedef struct Json {
    list_t *values;
} json_t;

#ifdef _PARSER_C
    json_t *JsonParse();
    void JsonFree(json_t *);
#else
    extern json_t *JsonParse();
    void JsonFree(json_t *);
#endif

#endif /* _PARSER_H */