#include "gut_api.h"
#include "gut_memory.h"
#include "gut_lexer.h"


#define INITIAL_STACK_SIZE 256

// NOTE (Emil): This might not be the best way of doing this.
static GutGlobalState globalState;


GutState * GutNewState (void)
{
    GutState * state = MALLOC(GutState *, sizeof(GutState));
    state->globalState = &globalState;
    state->function = MALLOC(GutFunction *, sizeof(GutFunction));

    state->lexer = MALLOC(GutLexerState *, sizeof(GutLexerState));
    GutLexerInit(state->lexer);

    state->stack_size = INITIAL_STACK_SIZE;
    state->stack = MALLOC(StackPtr, INITIAL_STACK_SIZE);
    state->program_counter = state->stack;
    state->stack_pointer = state->stack;
    state->frame_pointer = state->stack;

    return state;
}


GutTValue GutPop (GutState * state)
{
    return *(state->stack_pointer--);
}
