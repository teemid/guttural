#include "gut_array.h"
#include "gut_function.h"
#include "gut_hashtable.h"
#include "gut_memory.h"


GutFunction * GutFunctionNew (GutFunction * parent)
{
    GutFunction * function = Allocate(GutFunction *, sizeof(GutFunction));
    function->parent = parent;
    function->functions = NULL;
    function->function_count = 0;
    function->constants = NULL;
    function->code = NULL;
    function->arity = 0;

    return function;
}


void GutFunctionIntializeFunctions (GutFunction * function, UInt32 initialSize)
{
    function->functions = Buffer(GutFunction, initialSize);
}


void GutFunctionDelete (GutFunction * function)
{
    GutArrayDelete(function->constants);
    Free(function->code);
    Free(function);
}
