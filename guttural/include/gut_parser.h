#ifndef GUTTURAL_PARSER_H
#define GUTTURAL_PARSER_H


#include "gut_state.h"


typedef enum {
    PRECEDENCE_NONE,
    PRECEDENCE_LOWEST,
    PRECEDENCE_ASSIGNMENT,  // =
    PRECEDENCE_LOGICAL_OR,  // ||
    PRECEDENCE_LOGICAL_AND, // &&
    PRECEDENCE_EQUALITY,    // == !=
    PRECEDENCE_COMPARISON,  // < > <= >=
    PRECEDENCE_TERM,        // + -
    PRECEDENCE_FACTOR,      // * /
    PRECEDENCE_UNARY,       // - !
    PRECEDENCE_CALL,        // . () [] {}
} Precedence;


typedef void (* GrammarFunctionPtr) (GutState * state);


typedef struct GrammarRule {
    GrammarFunctionPtr prefix;
    GrammarFunctionPtr infix;
    Precedence precedence;
    char * name;
} GrammarRule;


void GutParse (GutState * state);
void GutParserSetInput (GutState * state, char * buffer);


#endif
