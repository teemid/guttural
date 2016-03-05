#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H


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


const char * const guttural_tokens[];


enum GutturalTokenType {
    TOKEN_NUMBER = LAST_RESERVED,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_IDENTIFIER
};


typedef struct GutturalToken {
    int type;
    char * data;
} GutturalToken;


typedef struct GutturalLexerState
{
    int current;
    int linenumber;
    GutturalToken t;
    GutturalToken lookahead;
    int stack_top;
    int stack_base;
    int stack_last;
    char * input;
    char * source;
} GutturalLexerState;


void guttural_lexer_set_input (GutturalLexerState * state, char * input);
void guttural_lexer_next (GutturalLexerState * state);
void guttural_lexer_lookahead (GutturalLexerState * state);


#endif
