#ifndef GUTTURAL_STATE_H
#define GUTTURAL_STATE_H


#include "gut_object.h"
#include "gut_function.h"


typedef struct GutturalGlobalState
{
    GutturalFunction * functions;
} GutturalGlobalState;


typedef GutturalTaggedValue * StkId;


typedef struct GutturalState
{
    int pc;
    int sp;
    int fp;

    GutturalGlobalState * globalState;

    int stackSize;
    int * stack;

    int * instructions;
} GutturalState;


#endif
