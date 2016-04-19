#include <stdio.h>

#include "gut_lexer.h"
#include "gut_object.h"


const char * const guttural_tokens[] = {
    "TOKEN_FUNCTION",
    "TOKEN_RETURN",
    "TOKEN_IF",
    "TOKEN_ELSEIF",
    "TOKEN_ELSE",
    "TOKEN_END",
    "TOKEN_TRUE",
    "TOKEN_FALSE",
    "TOKEN_IDENTIFIER",
    "TOKEN_INTEGER",
    "TOKEN_DOUBLE",
    "TOKEN_STRING",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_MULT",
    "TOKEN_DIV",
    "TOKEN_EQ",
    "TOKEN_PAREN_OPEN",
    "TOKEN_PARENT_CLOSE",
    "TOKEN_SQUARE_OPEN",
    "TOKEN_SQUARE_CLOSE",
    "TOKEN_CURLY_OPEN",
    "TOKEN_CURLY_CLOSE",
    "TOKEN_PERIOD",
    "TOKEN_COMMA",
    "TOKEN_EOF"
};


const char * const guttural_keywords[] = {
    "function",
    "return",
    "if",
    "elseif",
    "else",
    "end",
    "true",
    "false"
};

#define KeywordCount (sizeof(guttural_keywords) / sizeof(char *))


static void lex (GutLexerState * state);


static GutValue nil;

#define SetTokenType(state, gut_type) (state)->token.type = (gut_type)
#define SetLookahead(state, gut_type) (state)->lookahead.type = (gut_type)


GutLexerInit (GutLexerState * state)
{
    state->colnumber = 0;
    state->linenumber = 0;

    SetTokenType(state, TOKEN_EOF);
    SetLookahead(state, TOKEN_EOF);

    state->input = NULL;
}


GutLexerSetInput (GutLexerState * state, char * input)
{
    state->input = input;
}


GutLexerNext (GutLexerState * state)
{
    lex(state);
}




#define Curr(state) (state)->input[(state)->colnumber]
#define Peek(state) (state)->input[(state)->colnumber + 1]

#define Next(state) (state)->colnumber++;


#define IsDigit(c) ('0' <= (c) && (c) <= '9')
#define IsCharacter(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

#define IsValidIdentifierStart(c) (IsCharacter(c) || (c) == '_')
#define IsValidIdentifierContinuation(c) (IsCharacter(c) || IsDigit(c) || (c) == '_')

#define SetErrorMessage(message, line, col)


static Bool32 CompareKeyword (char * start, char * end, const char * keyword)
{
    UInt32 length = (end - start);

    if (strlen(keyword) != length) { return 0; }

    for (UInt32 i = 0; i < length; i++)
    {
        if (*(start + i) != *(keyword + i)) { return 0; }
    }

    return 1;
}


static void checkIfKeyword (GutLexerState * state, char * start, char * end)
{
    for (UInt32 i = 0; i < KeywordCount; i++)
    {
        if (CompareKeyword(start, end, guttural_keywords[i]))
        {
            SetTokenType(state, i);
            return;
        }
    }
}


static void lexIdentifier (GutLexerState * state)
{
    char * start = &Curr(state);

    char c = Curr(state);
    if (!IsValidIdentifierStart(c))
    {
        SetErrorMessage("Not a valid identifier", state->linenumber, state->colnumber)
    }

    while (IsValidIdentifierContinuation(Curr(state)))
    {
        Next(state);
    }

    char * end = &Curr(state);

    SetTokenType(state, TOKEN_IDENTIFIER);

    checkIfKeyword(state, start, end);
}


static void lexNumber (GutLexerState * state)
{
    char * start = &Curr(state);

    while (IsDigit(Curr(state)))
    {
        Next(state);
    }

    SetTokenType(state, TOKEN_INTEGER);

    if (Curr(state) == '.')
    {
        Next(state);

        while (IsDigit(Curr(state)))
        {
            Next(state);
        }

        SetTokenType(state, TOKEN_DOUBLE);
    }

    char * end = &Curr(state);
}


// NOTE (Emil): Main lexer loop
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
                lexIdentifier(state);
            } return;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                lexNumber(state);
            } return;
            case '\'': case '"':
            {
                char delimiter = c;
                Next(state);

                while (Curr(state) != delimiter)
                {
                    Next(state);
                }

                SetTokenType(state, TOKEN_STRING);
                Next(state);
            } return;
            case '+':
            {
                SetTokenType(state, TOKEN_PLUS);
                Next(state);
            } return;
            case '-':
            {
                SetTokenType(state, TOKEN_MINUS);
                Next(state);
            } return;
            case '*':
            {
                SetTokenType(state, TOKEN_MULT);
                Next(state);
            } return;
            case '/':
            {
                SetTokenType(state, TOKEN_DIV);
                Next(state);
            } return;
            case '=':
            {
                SetTokenType(state, TOKEN_EQ);
                Next(state);
            } return;
            case '(':
            {
                SetTokenType(state, TOKEN_PAREN_OPEN);
                Next(state);
            } return;
            case ')':
            {
                SetTokenType(state, TOKEN_PAREN_CLOSE);
                Next(state);
            } return;
            case '[':
            {
                SetTokenType(state, TOKEN_SQUARE_OPEN);
                Next(state);
            } return;
            case ']':
            {
                SetTokenType(state, TOKEN_SQUARE_CLOSE);
                Next(state);
            } return;
            case '{':
            {
                SetTokenType(state, TOKEN_CURLY_OPEN);
                Next(state);
            } return;
            case '}':
            {
                SetTokenType(state, TOKEN_CURLY_CLOSE);
                Next(state);
            } return;
            case '.':
            {
                SetTokenType(state, TOKEN_PERIOD);
                Next(state);
            } return;
            case ',':
            {
                SetTokenType(state, TOKEN_COMMA);
                Next(state);
            } return;
            case '\0':
            {
                SetTokenType(state, TOKEN_EOF);
            } return;
            case '#':
            {
                Next(state);

                while (Curr(state) != '\n' && Curr(state) != '\r')
                {
                    Next(state);
                }
                state->linenumber++;
            }
            case '\r': case '\n':
            {
                if (Peek(state) == '\n')
                {
                    Next(state);
                }
                state->linenumber++;
            }
        }

        Next(state);
    }
}
