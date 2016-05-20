#ifndef GUTTURAL_STATE_H
#define GUTTURAL_STATE_H


#include "gut_function.h"
#include "gut_hashtable.h"
#include "gut_lexer.h"
#include "gut_object.h"


typedef struct GutturalGlobalState
{
    GutTable * variables;
    GutTable * strings;
} GutGlobalState;


typedef struct GutturalState
{
    GutGlobalState * globalState;
    GutFunction * function;

    GutLexerState * lexer;

    Int32 stack_size;
    StackPtr stack;

    UInt64 program_counter;
    StackPtr stack_pointer;
    StackPtr frame_pointer;
} GutState;


#define Global(gut_state) (gut_state)->globalState


#endif
