#include "lexer.h"
#include <stdio.h>
#include "parson.h"

int main(int argc, char **argv) {
    json_t *j =  parsonParse(argv[1]);
    // parsonPrettify(j, 0);
    parsonFree(j);
    
}