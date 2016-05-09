#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H


#include "gut_types.h"


enum GutturalReserved
{
    TOKEN_ELSE,
    TOKEN_ELSEIF,
    TOKEN_END,
    TOKEN_FALSE,
    TOKEN_FUNCTION,
    TOKEN_IF,
    TOKEN_LET,
    TOKEN_RETURN,
    TOKEN_THEN,
    TOKEN_TRUE,
    LAST_RESERVED
};


enum GutturalTokenType {
    TOKEN_PLUS = LAST_RESERVED,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_EQ,
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_DOUBLE,
    TOKEN_STRING,
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


typedef union GutturalSemanticInformation {
    Int64 integer;
    Real64 real;
} GutSemInfo;


typedef struct GutturalToken {
    UInt32 type;
    GutSemInfo semantics;
} GutToken;


typedef struct GutturalLexerState
{
    UInt32 position;

    UInt32 colnumber;
    UInt32 linenumber;

    GutToken token;
    GutToken lookahead;

    void * temp;
    char * input;
} GutLexerState;


void GutLexerInit (GutLexerState * lexer);
UInt32 GutLexerNext (GutLexerState * lexer);
UInt32 GutLexerPeek (GutLexerState * lexer);


#endif
