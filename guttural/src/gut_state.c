#include "gut_common.h"
#include "gut_conf.h"
#include "gut_lexer.h"
#include "gut_memory.h"
#include "gut_object.h"
#include "gut_state.h"
#include "gut_string.h"
#include "guttural.h"


// NOTE (Emil): This might not be the best way of doing this.
static GutGlobalState * global_state;


internal GutTValue * NewValue (GutType type)
{
    GutTValue * tagged_value = Allocate(GutTValue *, sizeof(GutTValue));

    tagged_value->type = type;

    return tagged_value;
}


GutTValue * NewString (char * string, Size length)
{
    GutTValue * tagged_value = NewValue(TYPE_STRING);
    tagged_value->value.string = Allocate(GutString *, sizeof(GutString));

    String(tagged_value)->c_str = string;
    String(tagged_value)->length = length;
    String(tagged_value)->hash = 0;

    global_state->string_table->hash(tagged_value);

    return tagged_value;
}



internal GutGlobalState * NewGlobalState (void)
{
    GutGlobalState * g_state = Allocate(GutGlobalState *, sizeof(GutGlobalState));
    g_state->variables = GutTableNew(0);
    g_state->string_table = GutTableNew(0);

    return g_state;
}


GutState * GutNewState (void)
{
    if (NULL == global_state)
    {
        global_state = NewGlobalState();
    }

    GutState * state = Allocate(GutState *, sizeof(GutState));
    state->global_state = global_state;
    state->function = GutFunctionNew(NULL);

    state->lexer = Allocate(GutLexerState *, sizeof(GutLexerState));
    GutLexerInit(state);

    state->stack_size = INITIAL_STACK_SIZE;
    state->stack = Allocate(StackPtr, INITIAL_STACK_SIZE);
    state->program_counter = 0;
    state->stack_pointer = state->stack;
    state->frame_pointer = state->stack;

    return state;
}


#define GlobalStringTable(state) (state)->global_state->string_table;


GutTValue * GutAddString (GutState * state, char * string, UInt32 length)
{
    GutTable * string_table = GlobalStringTable(state);
    GutTValue * tagged_string = NewString(string, length);

    UInt32 hash = string_table->hash(tagged_string);

    GutTValue * existing = GutTableHashGet(string_table, hash);

    if (Type(existing) == TYPE_NIL)
    {
        String(tagged_string)->hash = hash;
        GutTableHashAdd(string_table, hash, tagged_string, tagged_string);
    }
    else
    {
        GutStringDelete(tagged_string);
        tagged_string = existing;
    }

    return tagged_string;
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
