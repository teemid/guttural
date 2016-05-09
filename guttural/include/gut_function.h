#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H


#include "gut_array.h"
#include "gut_hashtable.h"
#include "gut_types.h"


typedef struct GutturalFunction GutFunction;
typedef UByte Instruction;


struct GutturalFunction
{
    GutFunction * parent;
    GutTable * variables;
    GutArray * code;
};


GutFunction * GutFunctionNew (void);
void GutFunctionDelete (GutFunction * function);


#endif
