#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H


#include "gut_types.h"


typedef struct GutturalFunction
{
    struct GutturalFunction * parent;
    UByte * code;
} GutFunction;


#endif
