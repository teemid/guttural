#include <stdio.h>

#include "guttural.h"
#include "gut_hashtable.h"
#include "gut_object.h"
#include "gut_memory.h"


#define GetSemanticsInt(state) (state)->lexer->token.semantics.i
#define GetSemanticsReal(state) (state)->lexer->token.semantics.r


static GutTValue NewInteger (Real64 value)
{
    GutTValue tagged = { { value }, TYPE_INTEGER };

    return tagged;
}


static GutTValue NewDouble (Real64 value)
{
    GutTValue tagged = { { 0 }, TYPE_DOUBLE };
    Double(tagged) = value;

    return tagged;
}


static GutTValue NewString (char * c_str)
{
    GutTValue tagged = { { 0 }, TYPE_STRING };
    GutString * string = tagged.value.string;
    string->c_str = c_str;

    return tagged;
}


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    // GutTable * table = GutTableNew(10);

    // GutTableAdd(table, NewString("a"), NewInteger(10));
    // GutTableAdd(table, NewString("b"), NewInteger(10));
    // GutTableAdd(table, NewString("c"), NewDouble(2.0));

    // GutTValue value = GutTableGet(table, NewString("a"));

    // printf("%s: %d\n", guttural_types[Type(value)], (int)Integer(value));

    // GutTableDelete(table);

    GutState * state = GutNewState();

    GutDoFile(state, argv[1]);

    return 0;
}
