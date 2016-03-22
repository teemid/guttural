#include <stddef.h>
#include <stdio.h>


#include "gut_conf.h"
#include "gut_opcode.h"
#include "gut_memory.h"
#include "gut_vm.h"


static GutGlobalState * globals;


static void GutVMInit ( GutState * state )
{
    state->pc = 0;
    state->sp = 0;
    state->fp = 0;

    state->stack = (int *)MALLOC(256 * sizeof(int));
}


static void GutVMCleanUp ( GutState * state )
{
}

#ifdef TRACE

static void GutPrintStack ( GutState * state )
{

}


#endif

#define push(state, value) (state->stack[state->sp++] = (value))
#define pop() (state->stack[state->sp--])


void GutVMExecute(GutState * state) { }
