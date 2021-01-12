#include <_stdio.h>
#include <stdio.h>
/*
 * Token types
 */
typedef enum Token {
    Tok_BraceOpen,
    Tok_BraceClose,
    Tok_ParenOpen,
    Tok_ParenClose,
    Tok_Eof,
    Tok_Key,
    Tok_String,
    Tok_Number,
    Tok_Separator,
    Tok_Bool,
    Tok_End,
} token;

#if defined (_LEXER_C)
    token getNextToken();
    void advance();
    char buffer[];
    FILE *Istream;
#else
    extern token getNextToken();
    extern void advance();
    extern char buffer[];
    extern FILE *Istream;
#endif