#include <stdio.h>
#include <string.h>

#include "guttural.h"
#include "gut_hashtable.h"
#include "gut_object.h"
#include "gut_memory.h"


#define GetSemanticsInt(state) (state)->lexer->token.semantics.i
#define GetSemanticsReal(state) (state)->lexer->token.semantics.r


static GutTValue * NewInteger (Int64 value)
{
    GutTValue * tagged = Allocate(GutTValue *, sizeof(GutTValue));
    Type(tagged) = TYPE_INTEGER;
    Integer(tagged) = value;

    return tagged;
}


static GutTValue * NewDouble (Real64 value)
{
    GutTValue * tagged = Allocate(GutTValue *, sizeof(GutTValue));
    Type(tagged) = TYPE_DOUBLE;
    Double(tagged) = value;

    return tagged;
}


static GutTValue * NewString (char * c_str)
{
    GutTValue * tagged = Allocate(GutTValue *, sizeof(GutTValue));
    Type(tagged) = TYPE_STRING;
    String(tagged) = Allocate(GutString *, sizeof(GutString));
    String(tagged)->c_str = c_str;
    String(tagged)->length = strlen(c_str);

    return tagged;
}


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    GutTable * table = GutTableNew(10);

    GutTableAdd(table, NewString("a"), NewInteger(10));
    GutTableAdd(table, NewString("b"), NewInteger(20));
    GutTableAdd(table, NewString("c"), NewDouble(2.0));

    GutTableResize(table, 20);

    GutTableRemoveHash(table, NewString("c"));

    GutTValue * value = GutTableGetHash(table, NewString("c"));

    printf("%s: %f\n", guttural_types[Type(value)], (double)Double(value));

    GutTableDelete(table);

    GutState * state = GutNewState();

    GutDoFile(state, argv[1]);

    return 0;
}
