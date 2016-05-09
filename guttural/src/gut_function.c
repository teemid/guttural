#include "gut_array.h"
#include "gut_function.h"
#include "gut_hashtable.h"
#include "gut_memory.h"


GutFunction * GutFunctionNew (void)
{
    GutFunction * function = Allocate(GutFunction *, sizeof(GutFunction));
    function->variables = GutTableNew(0);
    function->code = GutArrayNew(0);

    return function;
}


void GutFunctionDelete (GutFunction * function)
{
    GutTableDelete(function->variables);
    GutArrayDelete(function->code);
    Free(function);
}
