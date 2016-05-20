#include <stdio.h>

#include "gut_common.h"
#include "gut_memory.h"
#include "gut_state.h"
#include "gut_parser.h"


internal char * read_source_file (char * filename)
{
    FILE * file;
    file = fopen(filename, "rb");

    Assert(file, "Could not find file.");

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


void GutDoFile (GutState * state, char * filename)
{
    char * buffer = read_source_file(filename);

    printf(buffer);

    state->lexer->input = buffer;

    GutParse(state);
}
