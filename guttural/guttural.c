#include <stdio.h>

#include "gut_memory.h"
#include "gut_lexer.h"
#include "gut_types.h"


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

int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    char * buffer = read_source_file(argv[1]);

    printf(buffer);

    GutLexerState lexer;
    GutLexerInit(&lexer);
    GutLexerSetInput(&lexer, buffer);

    while (1)
    {
        GutLexerNext(&lexer);

        PrintToken(&lexer);

        if (lexer.token.type == TOKEN_EOF)
        {
            break;
        }
    }

    return 0;
}
