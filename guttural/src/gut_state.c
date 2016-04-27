#include "gut_api.h"
#include "gut_conf.h"
#include "gut_lexer.h"
#include "gut_memory.h"
#include "gut_object.h"


// NOTE (Emil): This might not be the best way of doing this.
static GutGlobalState globalState;


GutState * GutNewState (void)
{
    GutState * state = Allocate(GutState *, sizeof(GutState));
    state->globalState = &globalState;
    state->function = Allocate(GutFunction *, sizeof(GutFunction));

    state->lexer = Allocate(GutLexerState *, sizeof(GutLexerState));
    GutLexerInit(state->lexer);

    state->stack_size = INITIAL_STACK_SIZE;
    state->stack = Allocate(StackPtr, INITIAL_STACK_SIZE);
    state->program_counter = state->stack;
    state->stack_pointer = state->stack;
    state->frame_pointer = state->stack;

    return state;
}


void GutPush (GutState * state, void * value, GutType type)
{
}


void GutPushNil (GutState * state)
{
}

void GutPushInteger (GutState * state, Int64 i)
{

}

void GutPushDouble (GutState * state, Real64 d)
{

}

void GutPushBoolean (GutState * state, Bool32 b)
{

}


GutTValue GutPop (GutState * state)
{
    return *(state->stack_pointer--);
}


void GutRegister(GutState * state, GutCFunction function)
{
    GutGlobalState * global = Global(state);
}
