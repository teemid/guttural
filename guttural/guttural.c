#include <stdio.h>

#include "gut_lexer.h"
#include "gut_memory.h"


static char * read_source_file (char * filename)
{
    FILE * file;
    file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char * buffer = MALLOC(char *, size);

    size_t result = fread(buffer, 1, size, file);

    if (!result)
    {
        printf("Reading error");
    }

    fclose(file);

    return buffer;
}


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        printf(argv[i] + '\n');
    }

    char * buffer = read_source_file(argv[1]);

    printf(buffer);

    GutturalLexerState lexer;
    guttural_lexer_set_input(&lexer, buffer);

    guttural_lexer_next(&lexer);

    printf("%d", lexer.t.type);

    return 0;
}