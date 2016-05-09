#include <stddef.h>
#include <stdio.h>

#include "guttural.h"
#include "gut_opcodes.h"
#include "gut_memory.h"
#include "gut_vm.h"


static GutGlobalState * globals = NULL;


#define ProgramCounter(state) (state)->program_counter


void GutVMExecute(GutState * state)
{
    for (;;)
    {
        switch (ProgramCounter(state))
        {
            case OP_GET_LOCAL:
            {

            } break;
            case OP_SET_LOCAL:
            {

            } break;
            case OP_GET_GLOBAL:
            {

            } break;
            case OP_SET_GLOBAL:
            {

            } break;
        }
    }
}
