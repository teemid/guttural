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
    Int32 pc;
    Int32 sp;
    Int32 fp;

    GutGlobalState * globalState;

    Int32 stackSize;
    Int32 * stack;

    Int32 * instructions;
} GutState;


#endif
