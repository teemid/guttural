#include <stdlib.h>

#include "gut_lexer.h"


void guttural_lexer_set_input (GutturalLexerState * state, char * source)
{
    state->current = 0;
    state->linenumber = 0;
    state->lookahead;
    state->input = source;
    // NOTE (Emil): This is meant to hold the source filename.
    state->source = "";
}

void guttural_lexer_next (GutturalLexerState * state)
{

}

#define curr(state) state->input[state->current]
#define is_number(state) curr(state) >= '0' && curr(state) <= '9'
#define is_first_identifier(state) \
    curr(state) >= 'a' && curr(state) <= 'z' && \
    curr(state) >= 'A' && curr(state) <= 'Z' && curr(state) == '_'
#define is_identifier(state) is_first_identifier(state) && is_number(state)



static void lex (GutturalLexerState * state)
{
    char c;

    for (;;)
    {
        switch (c = state->input[state->current])
        {
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
            case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
            case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z':
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
            case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
            case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z':
            {
                state->t.type = TOKEN_IDENTIFIER;
            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                while (is_number(state)) { }

                state->t.type = TOKEN_NUMBER;
                state->t.data = (void *)0;
            } return;
            case '\'': case '"':
            {
                char delimiter = c;

                while (curr(state) != delimiter)
                {
                    state->current++;
                }

                return;
            }
            case '\r': case '\n':
            {
                if (state->input[state->current++] == '\n')
                {

                }
                state->linenumber++;
            }
        }

        state->current++;
    }
}
