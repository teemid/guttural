#include "gut_array.h"
#include "gut_function.h"
#include "gut_hashtable.h"
#include "gut_memory.h"


GutFunction * GutFunctionNew (GutFunction * parent)
{
    GutFunction * function = Allocate(GutFunction *, sizeof(GutFunction));
    function->parent = parent ? parent : NULL;
    function->arity = 0;
    function->variables = GutTableNew(0);
    function->constants = GutArrayNew(0);
    function->code = Buffer(Instruction, 20);

    return function;
}


void GutFunctionDelete (GutFunction * function)
{
    GutTableDelete(function->variables);
    Free(function->code);
    Free(function);
}
