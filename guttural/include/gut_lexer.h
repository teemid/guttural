#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H


#include "gut_types.h"


enum GutturalResered
{
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_IF,
    TOKEN_ELSEIF,
    TOKEN_ELSE,
    TOKEN_END,
    TOKEN_TRUE,
    TOKEN_FALSE,
    LAST_RESERVED
};


enum GutturalTokenType {
    TOKEN_IDENTIFIER = LAST_RESERVED,
    TOKEN_INTEGER,
    TOKEN_DOUBLE,
    TOKEN_STRING,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_EQ,
    TOKEN_PAREN_OPEN,
    TOKEN_PAREN_CLOSE,
    TOKEN_SQUARE_OPEN,
    TOKEN_SQUARE_CLOSE,
    TOKEN_CURLY_OPEN,
    TOKEN_CURLY_CLOSE,
    TOKEN_PERIOD,
    TOKEN_COMMA,
    TOKEN_EOF
};


extern const char * const guttural_tokens[];


typedef struct GutturalToken {
    UInt32 type;
    char * data;
} GutToken;


typedef struct GutturalLexerState
{
    UInt32 colnumber;
    UInt32 linenumber;

    GutToken token;
    GutToken lookahead;

    void * temp;
    char * input;
} GutLexerState;

GutLexerInit     (GutLexerState * state);
GutLexerSetInput (GutLexerState * state, char * input);
GutLexerNext     (GutLexerState * state);

#endif
