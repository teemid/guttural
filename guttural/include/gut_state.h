#ifndef GUTTURAL_STATE_H
#define GUTTURAL_STATE_H


#include "gut_function.h"
#include "gut_hashtable.h"
#include "gut_lexer.h"
#include "gut_object.h"


typedef struct GutturalGlobalState
{
    GutTable * variables;
    GutTable * string_table;
} GutGlobalState;


typedef struct CallFrame
{
    Instruction * ip;
    GutFunction * function;
    StackPtr stack_start;
} CallFrame;


typedef struct GutturalState
{
    GutGlobalState * global_state;
    GutFunction * function;

    CallFrame * callframes;
    UInt32 callframe_count;
    UInt32 callframe_capacity;

    GutLexerState * lexer;

    Int32 stack_size;
    StackPtr stack;
    StackPtr top;

    UInt64 program_counter;
    StackPtr stack_pointer;
    StackPtr frame_pointer;
} GutState;


#define Global(gut_state) (gut_state)->global_state


GutTValue * NewString  (char * string, Size length);
GutTValue * NewInteger (UInt64 i);
GutTValue * NewDouble  (Real64 d);


GutTValue * GutAddString    (GutState * state, char * string, UInt32 length);


#endif
