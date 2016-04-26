#include <stdio.h>

#include "gut_lexer.h"
#include "gut_object.h"


const char * const guttural_tokens[] = {
    "TOKEN_ELSE",
    "TOKEN_ELSEIF",
    "TOKEN_END",
    "TOKEN_FALSE",
    "TOKEN_FUNCTION",
    "TOKEN_IF",
    "TOKEN_LET",
    "TOKEN_RETURN",
    "TOKEN_THEN",
    "TOKEN_TRUE",
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
    "else",
    "elseif",
    "end",
    "false",
    "function",
    "if",
    "let",
    "return",
    "then",
    "true"
};


#define KeywordCount (sizeof(guttural_keywords) / sizeof(char *))
#define internal static


internal void lex (GutLexerState * state);


static GutValue nil;

#define SetTokenType(state, gut_type) (state)->token.type = (gut_type)
#define SetLookahead(state, gut_type) (state)->lookahead.type = (gut_type)


GutLexerInit (GutLexerState * lexer)
{
    lexer->position = 0;
    lexer->colnumber = 0;
    lexer->linenumber = 0;

    SetTokenType(lexer, TOKEN_EOF);
    SetLookahead(lexer, TOKEN_EOF);

    lexer->input = NULL;
}


GutLexerNext (GutLexerState * lexer)
{
    lex(lexer);
}

GutLexerPeek (GutLexerState * lexer)
{
    lex(lexer);
}


#define Curr(lexer) (lexer)->input[(lexer)->position]
#define Peek(lexer) (lexer)->input[(lexer)->position + 1]

#define Next(lexer) (lexer)->position++;
#define NewLine(lexer) (lexer)->linenumber++; (lexer)->colnumber = 0


#define IsDigit(c) ('0' <= (c) && (c) <= '9')
#define IsCharacter(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

#define IsValidIdentifierStart(c) (IsCharacter(c) || (c) == '_')
#define IsValidIdentifierContinuation(c) (IsCharacter(c) || IsDigit(c) || (c) == '_')

#define SetErrorMessage(message, line, col)


internal Bool32 CompareKeyword (char * start, char * end, const char * keyword)
{
    UInt32 length = (end - start);

    if (strlen(keyword) != length) { return 0; }

    for (UInt32 i = 0; i < length; i++)
    {
        if (*(start + i) != *(keyword + i)) { return 0; }
    }

    return 1;
}


internal void checkIfKeyword (GutLexerState * lexer, char * start, char * end)
{
    for (UInt32 i = 0; i < KeywordCount; i++)
    {
        if (CompareKeyword(start, end, guttural_keywords[i]))
        {
            SetTokenType(lexer, i);
            return;
        }
    }
}


internal void lexIdentifier (GutLexerState * lexer)
{
    char * start = &Curr(lexer);

    char c = Curr(lexer);
    if (!IsValidIdentifierStart(c))
    {
        SetErrorMessage("Not a valid identifier", lexer->linenumber, lexer->colnumber)
    }

    while (IsValidIdentifierContinuation(Curr(lexer)))
    {
        Next(lexer);
    }

    char * end = &Curr(lexer);

    SetTokenType(lexer, TOKEN_IDENTIFIER);

    checkIfKeyword(lexer, start, end);
}


internal void lexNumber (GutLexerState * lexer)
{
    char * start = &Curr(lexer);

    while (IsDigit(Curr(lexer)))
    {
        Next(lexer);
    }

    SetTokenType(lexer, TOKEN_INTEGER);

    if (Curr(lexer) == '.')
    {
        Next(lexer);

        while (IsDigit(Curr(lexer)))
        {
            Next(lexer);
        }

        SetTokenType(lexer, TOKEN_DOUBLE);
    }

    char * end = &Curr(lexer);
}


// NOTE (Emil): Main lexer loop
internal void lex (GutLexerState * lexer)
{
    char c;

    for (;;)
    {
        switch (c = Curr(lexer))
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
                lexIdentifier(lexer);
            } return;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                lexNumber(lexer);
            } return;
            case '\'': case '"':
            {
                char delimiter = c;
                Next(lexer);

                while (Curr(lexer) != delimiter)
                {
                    Next(lexer);
                }

                SetTokenType(lexer, TOKEN_STRING);
                Next(lexer);
            } return;
            case '+':
            {
                SetTokenType(lexer, TOKEN_PLUS);
                Next(lexer);
            } return;
            case '-':
            {
                SetTokenType(lexer, TOKEN_MINUS);
                Next(lexer);
            } return;
            case '*':
            {
                SetTokenType(lexer, TOKEN_MULT);
                Next(lexer);
            } return;
            case '/':
            {
                SetTokenType(lexer, TOKEN_DIV);
                Next(lexer);
            } return;
            case '=':
            {
                SetTokenType(lexer, TOKEN_EQ);
                Next(lexer);
            } return;
            case '(':
            {
                SetTokenType(lexer, TOKEN_PAREN_OPEN);
                Next(lexer);
            } return;
            case ')':
            {
                SetTokenType(lexer, TOKEN_PAREN_CLOSE);
                Next(lexer);
            } return;
            case '[':
            {
                SetTokenType(lexer, TOKEN_SQUARE_OPEN);
                Next(lexer);
            } return;
            case ']':
            {
                SetTokenType(lexer, TOKEN_SQUARE_CLOSE);
                Next(lexer);
            } return;
            case '{':
            {
                SetTokenType(lexer, TOKEN_CURLY_OPEN);
                Next(lexer);
            } return;
            case '}':
            {
                SetTokenType(lexer, TOKEN_CURLY_CLOSE);
                Next(lexer);
            } return;
            case '.':
            {
                SetTokenType(lexer, TOKEN_PERIOD);
                Next(lexer);
            } return;
            case ',':
            {
                SetTokenType(lexer, TOKEN_COMMA);
                Next(lexer);
            } return;
            case '\0':
            {
                SetTokenType(lexer, TOKEN_EOF);
            } return;
            case '#':
            {
                Next(lexer);

                while (Curr(lexer) != '\n' && Curr(lexer) != '\r')
                {
                    Next(lexer);
                }
                lexer->linenumber++;
                lexer->colnumber = 0;
            }
            case '\r': case '\n':
            {
                if (Peek(lexer) == '\n')
                {
                    Next(lexer);
                }
                lexer->linenumber++;
                lexer->colnumber = 0;
            }
        }

        Next(lexer);
    }
}
