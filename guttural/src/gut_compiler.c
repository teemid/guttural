#include "gut_common.h"
#include "gut_compiler.h"
#include "gut_state.h"


internal void GutCompileFunction (GutState * state);


void GutCompile (GutState * state)
{
    GutCompileFunction(state);
}

internal void GutCompileFunction (GutState * state)
{
    UNUSED(state);
}
