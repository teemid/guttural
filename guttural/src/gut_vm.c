#include <stddef.h>
#include <stdio.h>


#include "gut_conf.h"
#include "gut_opcode.h"
#include "gut_memory.h"
#include "gut_vm.h"


static GutturalGlobalState * globals;


static void init_vm ( GutturalState * state )
{
    state->pc = 0;
    state->sp = 0;
    state->fp = 0;

    state->stack = MALLOC(int *, 256 * sizeof(int));
}


static void cleanup_vm ( GutturalState * state )
{
}

#ifdef TRACE

static void print_stack ( VirtualMachine * vm )
{
    int i;
    printf("\t[ ");
    for ( i = 0; i <= vm->stack_pointer; i++)
    {
        printf("%d, ", vm->stack[ i ]);
    }
    printf(" ]\n");
}


#endif

#define push(state, value) (state->stack[state->sp++] = (value))
#define pop() (state->stack[state->sp--])


void execute(GutturalState * state) { }
