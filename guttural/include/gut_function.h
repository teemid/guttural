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
    GutArray * constants;
    Instruction * code;
};


GutFunction * GutFunctionNew (void);
void GutFunctionDelete (GutFunction * function);

void GutFunctionSetVariable(GutFunction * function, GutTValue * identifier, GutTValue * value);
void GutFunctionDeleteVariable(GutFunction * function, GutTValue * identifier);

void GutFunctionSetCode(GutFunction * function);


#endif
