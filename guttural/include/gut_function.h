#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H


#include "gut_array.h"
#include "gut_hashtable.h"
#include "gut_types.h"


typedef struct GutturalFunction GutFunction;
typedef UByte Instruction;


struct GutturalFunction
{
    // The function this function is declared in.
    GutFunction * parent;
    // A list of functions declared in this function.
    GutTable * functions;
    // A table with all the names declared in this scope.
    GutTable * variables;
    // A list of all the constants declared in this scope.
    GutArray * constants;
    // The byte code for this function.
    Instruction * code;
};


GutFunction * GutFunctionNew (void);
void GutFunctionDelete (GutFunction * function);

void GutFunctionSetVariable(GutFunction * function, GutTValue * identifier, GutTValue * value);
void GutFunctionDeleteVariable(GutFunction * function, GutTValue * identifier);

void GutFunctionSetCode(GutFunction * function);


#endif
