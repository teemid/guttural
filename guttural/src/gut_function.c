#include "gut_array.h"
#include "gut_function.h"
#include "gut_hashtable.h"
#include "gut_memory.h"


GutFunction * GutFunctionNew (void)
{
    GutFunction * function = Allocate(GutFunction *, sizeof(GutFunction));
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
