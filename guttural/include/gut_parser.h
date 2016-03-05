#ifndef GUTTURAL_PARSER_H
#define GUTTURAL_PARSER_H


#include "gut_lexer.h"


typedef struct GutturalParserState
{
    GutturalLexerState * state;
} GutturalParserState;


void guttural_parser_init (GutturalParserState * state);


#endif
