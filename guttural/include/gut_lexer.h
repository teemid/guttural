#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H


#include "gut_types.h"


enum GutturalResered
{
    TOKEN_FUNCTION,
    TOKEN_IF,
    TOKEN_END,
    TOKEN_ELSE,
    TOKEN_ELSEIF,
    TOKEN_TRUE,
    TOKEN_FALSE,
    LAST_RESERVED
};


enum GutturalTokenType {
    TOKEN_NUMBER = LAST_RESERVED,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_IDENTIFIER
};

extern const char * const guttural_tokens[];


typedef struct GutturalToken {
    UInt32 type;
    char * data;
} GutToken;


typedef struct GutturalLexerState
{
    Int32 current;
    Int32 linenumber;
    GutToken token;
    GutToken lookahead;
    Int32 stack_top;
    Int32 stack_base;
    Int32 stack_last;
    char * input;
    char * source;
} GutLexerState;


void GutLexerSetInput (GutLexerState * state, char * input);
void GutLexerNext     (GutLexerState * state);
void GutLexerPeek     (GutLexerState * state);


#endif
