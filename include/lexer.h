#ifndef _LEXER_H
#define _LEXER_H

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
    char buffer[1024];
    FILE *Istream;
    char LastChar = ' ';
    int CurrentLine = 1;
#else
    extern token getNextToken();
    extern void advance();
    extern char buffer[];
    extern FILE *Istream;
    extern char LastChar;
    extern int CurrentLine;
#endif

#endif /* _LEXER_H */