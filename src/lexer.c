#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define _LEXER_C
#include "../include/lexer.h"
#undef __LEXER_C

/*
 * lexer.c
 *
 * Go through the source file and generate appropiate token for
 * every symbol
 */


/**
 * Current line in the input stream 
 */
static int CurrentLine = 1;

/** 
 * Lexeme
 */
char buffer[1024];

/** Last char */
static char LastChar = ' ';

/**
 * Advance to next character
 */
void advance() {
    LastChar = getc(Istream);
    if(LastChar == '\n') ++CurrentLine;
}

/**
 * Read a String
 */
token getIdentifier() {
    int i = 0;
    
    if(LastChar == '"') {
        advance();
        while(LastChar != '"') {
            buffer[i++] = LastChar;
            advance();
        }
        buffer[i] = 0;
        advance();
        while(isspace(LastChar)) {
            advance();
        }
        return LastChar == ':' ? Tok_Key : Tok_String;
    }

    if(isdigit(LastChar) || LastChar == '.') {
        while(isdigit(LastChar)) {
            buffer[i++] = LastChar;
            advance();
        }
        if(LastChar == '.') {
            buffer[i++] = '.';
            advance();
        }
        while(isdigit(LastChar)) {
            buffer[i++] = LastChar;
            advance();
        }
        buffer[i] = 0;
        return Tok_Number;
    }

    if(isalpha(LastChar)) {
        buffer[i++] = LastChar;
        advance();
        while(isalnum(LastChar)) {
            buffer[i++] = LastChar;
            advance();
        }
        buffer[i] = 0;
        if( strcmp(buffer, "True") == 0 || strcmp(buffer, "False") == 0 || strcmp(buffer, "null") == 0) {
            return Tok_Bool;
        }
        printf("Try enclosing `%s` in \"\" marks\n", buffer);
        exit(1);
    }

    printf("unexpected character '%c' on line %d\n", LastChar, CurrentLine);
    exit(1);
}

/*
 * Get token from input
 */
token getNextToken() {
    /* Skip whitespaces */
    while(isspace(LastChar)) {
        LastChar = getc(Istream);
    }
    
    while(LastChar != EOF) {
        switch(LastChar) {
            case '{': return Tok_BraceOpen;
            case '}': return Tok_BraceClose;
            case '[': return Tok_ParenOpen;
            case ']': return Tok_ParenClose;
            case ':': return Tok_Separator;
            case ',': return Tok_End;
            default : return getIdentifier();
        }
    }
    return Tok_Eof;
}

