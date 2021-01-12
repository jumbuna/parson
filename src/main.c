#include "../include/lexer.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Istream = fopen(argv[1], "r");
    int nest = -4;
    token x;
    while((x = getNextToken()) != Tok_Eof) {
        switch (x) {
        case Tok_Key: printf("%*s #%s ", nest, "", buffer);advance();break;
        case Tok_String: printf(" = %s (str) \n", buffer);advance();break;
        case Tok_Number: printf(" = %s (int) \n", buffer);advance();break;
        case Tok_Bool: printf(" = %s (keyword) \n", buffer);advance();break;
        case Tok_BraceOpen: nest += 4;printf("\n");advance();break;
        case Tok_BraceClose: nest -= 4;advance();break;
        case Tok_ParenOpen: printf("[\n");advance();break;
        case Tok_ParenClose: printf("] (arr)\n");
        default: advance();
        }
    }
}