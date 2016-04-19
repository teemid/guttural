#include <stdbool.h>
#include <stdlib.h>

#include "gut_lexer.h"


const char * const guttural_tokens[] = {
    "TOKEN_FUNCTION",
    "TOKEN_IF",
    "TOKEN_END",
    "TOKEN_ELSE",
    "TOKEN_ELSEIF",
    "TOKEN_TRUE",
    "TOKEN_FALSE",
    "TOKEN_NUMBER",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_MULT",
    "TOKEN_DIV",
    "TOKEN_OPEN_PAREN",
    "TOKEN_CLOSE_PAREN",
    "TOKEN_PERIOD",
    "TOKEN_IDENTIFIER"
};


static void lex (GutLexerState * state);


void GutLexerInit (GutLexerState * state)
{
    state->current = 0;
    state->linenumber = 0;
    state->lookahead;
    state->input = NULL;
    state->source = NULL;
}


void GutLexerNext (GutLexerState * state)
{
    if (state->input == NULL)
    {
    }

    lex(state);
}


#define Curr(state) state->input[state->current]
#define Peek(state) state->input[state->current + 1]
#define IsNumber(state) Curr(state) >= '0' && Curr(state) <= '9'
#define IsCharacter(state) \
    Curr(state) >= 'a' && Curr(state) <= 'z' && \
    Curr(state) >= 'A' && Curr(state) <= 'Z'
#define IsValidIdentifier(state) \
    IsCharacter(state) || IsNumber(state) || Curr(state) == '_'


static Bool32 compare (char * s1, size_t start1, char * s2, size_t start2, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if ((s1 + start1 + i) != (s2 + start2 + i))
        {
            return false;
        }
    }

    return true;
}


static void lex (GutLexerState * state)
{
    char c;

    for (;;)
    {
        switch (c = Curr(state))
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
            case '_':
            {
                UInt32 start = state->current;

                while (IsValidIdentifier(state)) { }

                state->token.type = TOKEN_IDENTIFIER;
                state->token.data = (void*)0;
            } return;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                UInt32 start = state->current;

                while (IsNumber(state)) { }

                state->token.type = TOKEN_NUMBER;
                // NOTE (Emil): Only Base 10 for the time being.
                char * end;
                strtol(state->input + start, &end, 10);
            } return;
            case '\'': case '"':
            {
                char delimiter = c;

                while (Curr(state) != delimiter)
                {
                    state->current++;
                }
            } return;
            case '(':
            {
                state->type = TOKEN_OPEN_PAREN;
            } return;
            case ')':
            {
                state->type = TOKEN_CLOSE_PAREN;
            }
            case '.':
            {
                state->type = TOKEN_PERIOD;
            }
            case '\r': case '\n':
            {
                if (Peek(state) == '\n')
                {

                }
                state->linenumber++;
            }
        }

        state->current++;
    }
}
