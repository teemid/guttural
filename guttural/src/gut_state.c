#include "guttural.h"
#include "gut_conf.h"
#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_memory.h"
#include "gut_object.h"
#include "gut_state.h"


// NOTE (Emil): This might not be the best way of doing this.
static GutGlobalState * globalState;


internal GutGlobalState * NewGlobalState (void)
{
    GutGlobalState * gState = Allocate(GutGlobalState *, sizeof(GutGlobalState));
    gState->variables = GutTableNew(0);
    gState->stringTable = GutTableNew(0);

    return gState;
}


GutState * GutNewState (void)
{
    if (NULL == globalState)
    {
        globalState = NewGlobalState();
    }

    GutState * state = Allocate(GutState *, sizeof(GutState));
    state->globalState = globalState;
    state->function = Allocate(GutFunction *, sizeof(GutFunction));

    state->lexer = Allocate(GutLexerState *, sizeof(GutLexerState));
    GutLexerInit(state->lexer);

    state->stack_size = INITIAL_STACK_SIZE;
    state->stack = Allocate(StackPtr, INITIAL_STACK_SIZE);
    state->program_counter = 0;
    state->stack_pointer = state->stack;
    state->frame_pointer = state->stack;

    return state;
}


// TODO (Emil): Check if we need to grow the stack.
void GutPush (GutState * state, GutValue value, GutType type)
{
    state->stack_pointer++;
    GutTValue * tagged = state->stack_pointer;
    tagged->value = value;
    tagged->type = type;
}


GutTValue GutPop (GutState * state)
{
    return *(state->stack_pointer--);
}


void GutRegister(GutState * state, GutCFunction function)
{
    GutGlobalState * global = Global(state);
    global;
    function;
}
