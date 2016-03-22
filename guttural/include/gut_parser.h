#ifndef GUTTURAL_PARSER_H
#define GUTTURAL_PARSER_H


#include "gut_lexer.h"


typedef struct GutturalParserState
{
    GutturalLexerState * state;
} GutParserState;


void GutParserInit (GutParserState * state);


#endif
