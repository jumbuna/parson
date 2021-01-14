#ifndef _PARSON_H
#define _PARSON_H

#include "../include/parser.h"

/* API */

struct Json *parsonParse(char *);

void parsonFree(struct Json *);

void *parsonGetByKey(struct Json *, char*);

_Bool parsonContains(struct  Json *, char *);

void parsonPrettify(struct Json *, int);

#endif /* _PARSON_H */