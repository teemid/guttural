#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H


#include "gut_array.h"
#include "gut_hashtable.h"
#include "gut_types.h"


// NOTE (Emil): Forward declaration because GutFunction refers to itself.
typedef struct GutturalFunction GutFunction;
typedef UByte Instruction;

struct GutturalFunction
{
    // The function this function is declared in.
    GutFunction * parent;
    // The number of parameters for the function.
    UInt8 arity;
    // A list of functions declared in this function.
    GutTable * functions;
    // A table with all the names declared in this scope.
    GutTable * variables;
    // A list of all the constants declared in this scope.
    GutArray * constants;
    // The byte code for this function.
    Instruction * code;
};


GutFunction * GutFunctionNew (GutFunction * parent);
void GutFunctionDelete (GutFunction * function);

void GutFunctionSetVariable(GutFunction * function, GutTValue * identifier, GutTValue * value);
void GutFunctionDeleteVariable(GutFunction * function, GutTValue * identifier);

void GutFunctionSetCode(GutFunction * function);


#endif
