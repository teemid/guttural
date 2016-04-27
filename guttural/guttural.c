#include <stdio.h>

#include "guttural.h"
#include "gut_common.h"
#include "gut_hashtable.h"
#include "gut_lexer.h"
#include "gut_object.h"
#include "gut_memory.h"


static char * read_source_file (char * filename)
{
    FILE * file;
    file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char * buffer = Allocate(char *, size + 1);
    buffer[size] = 0;

    size_t result = fread(buffer, 1, size, file);

    if (!result)
    {
        printf("Reading error");
    }

    fclose(file);

    return buffer;
}


static PrintToken(GutLexerState * state)
{
    printf("%s\n", guttural_tokens[state->token.type]);
}


#define GetSemanticsInt(state) (state)->lexer->token.semantics.i
#define GetSemanticsReal(state) (state)->lexer->token.semantics.r


void GutDoFile (GutState * state, char * filename)
{
    char * buffer = read_source_file(filename);

    printf(buffer);

    state->lexer->input = buffer;

    GutParse(state);
}


void PrintFunction (GutState * state)
{
    // Get the number of arguments.
    GutTValue tagged = GutPop(state);

    Int64 arg_count = Integer(tagged);

    for (int i = 0; i < arg_count; i++)
    {
        GutTValue value = GutPop(state);
    }
}

// typedef union GutturalValue
// {
//     Int64 i;
//     Real64 r;
//     char * string;
//     GutArray * array;
//     GutTable * table;
// } GutValue;


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


static GutTValue NewString (char * string)
{
    GutTValue tagged = { { 0 }, TYPE_STRING };
    String(tagged) = string;

    return tagged;
}


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    GutTValue keys[] = {
        NewString("a"),
        NewString("b"),
        NewString("c")
    };

    GutTable * table = GutTableNew(10);

    GutTValue a = NewInteger(10);
    GutTValue b = NewInteger(20);
    GutTValue c = NewDouble(2.0);

    GutTableAdd(table, &keys[0], a);
    GutTableAdd(table, &keys[1], b);
    GutTableAdd(table, &keys[2], c);

    GutTValue value = GutTableGet(table, &keys[0]);

    printf("%s: %d\n", guttural_types[Type(value)], (int)Integer(value));

    GutTableDelete(table);

    GutState * state = GutNewState();

    GutDoFile(state, argv[1]);

    return 0;
}
