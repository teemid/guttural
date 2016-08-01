#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H


#include "gut_array.h"
#include "gut_hashtable.h"
#include "gut_types.h"


// NOTE (Emil): Forward declaration because GutFunction refers to itself.
typedef struct GutturalFunction GutFunction;
typedef UInt32 Instruction;


struct GutturalFunction
{
    GutFunction * parent; // The function this function is declared in.
    GutFunction * functions; // A list of functions declared inside this function.
    UInt16 function_count; // The number of functions declared in the scope of this function.
    UInt8 arity; // The number of parameters for the function.
    GutArray * constants; // A list of all the constants declared in this scope.
    Instruction * code; // The byte code for this function.
};


GutFunction * GutFunctionNew (GutFunction * parent);
void GutFunctionDelete (GutFunction * function);


#endif
