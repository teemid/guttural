#include <stddef.h>
#include <stdio.h>


#include "gut_conf.h"
#include "gut_opcode.h"
#include "gut_memory.h"
#include "gut_vm.h"


static GutGlobalState * globals;

#define GutPush(state, value) (state->stack[state->stack_pointer++] = (value))
#define GutPop() (state->stack[state->stack_pointer--])


void GutVMExecute(GutState * state)
{
    for (;;)
    {

    }
}
