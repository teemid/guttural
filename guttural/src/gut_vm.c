#include <stddef.h>
#include <stdio.h>

#include "guttural.h"
#include "gut_common.h"
#include "gut_opcodes.h"
#include "gut_memory.h"
#include "gut_vm.h"


static GutGlobalState * globals = NULL;


#define GetCallframe(state)   (state)->callframes + (state)->callframe_count
#define GetInstruction(state) *(GetCallframe(state))->ip
#define GetCurrentFunction(state) (GetCallframe(state))->function

#define LoadConstant(state, index) GutArrayGet((GetCurrentFunction(state))->constants, index)


static void CallFunction (GutState * state)
{
    *state;
}


void GutVMExecute(GutState * state)
{
    for (;;)
    {
        Instruction i = GetInstruction(state);

        switch (OpCode(i))
        {
            case OP_LOAD:
            {
                GutTValue * a = LoadConstant(state, OperandA(i));
                UNUSED(a);
            } break;
            case OP_STORE:
            {

            } break;
            case OP_GLOAD:
            {

            } break;
            case OP_GSTORE:
            {

            } break;
            case OP_CALL:
            {
                CallFunction(state);
            }
        }
    }
}
