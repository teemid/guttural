#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H


#include "gut_types.h"


typedef struct GutturalFunction
{
    GutTable * local_variables;
    UByte * code;
} GutFunction;


#endif
