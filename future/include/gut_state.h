#ifndef GUTTURAL_STATE_H
#define GUTTURAL_STATE_H


#include "gut_object.h"
#include "gut_function.h"


typedef struct GutturalGlobalState
{
    GutFunction * functions;
} GutGlobalState;


typedef GutTValue * StkId;


typedef struct GutturalState
{
    GutGlobalState * globalState;

    Int32 stack_size;
    StackPtr stack;

    StackPtr program_counter;
    StackPtr stack_pointer;
    StackPtr frame_pointer;

    Int32 * instructions;

    UByte c_func_count;
} GutState;


#define Global(gut_state) (gut_state)->globalState


#endif
