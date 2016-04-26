#include <stdio.h>

#include "guttural.h"
#include "gut_lexer.h"
#include "gut_memory.h"


static char * read_source_file (char * filename)
{
    FILE * file;
    file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char * buffer = MALLOC(char *, size + 1);
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


void GutDoFile (GutState * state, char * filename)
{
    char * buffer = read_source_file(filename);

    printf(buffer);

    state->lexer->input = buffer;

    while (1)
    {
        GutLexerNext(state->lexer);

        Int32 type = state->lexer->token.type;

        printf("%s\n", guttural_tokens[type]);

        if (type == TOKEN_EOF)
        {
            break;
        }
    }
}


void PrintFunction (GutState * state)
{
    // Get the number of arguments.
    GutTValue value = GutPop(state);
}


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    GutState * state = GutNewState();

    GutDoFile(state, argv[1]);

    return 0;
}
