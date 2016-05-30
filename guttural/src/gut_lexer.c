#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_object.h"
#include "gut_string.h"
#include "gut_state.h"


const char * const guttural_tokens[] = {
    "TOKEN_ELSE",
    "TOKEN_ELSEIF",
    "TOKEN_END",
    "TOKEN_FALSE",
    "TOKEN_FUNCTION",
    "TOKEN_IF",
    "TOKEN_RETURN",
    "TOKEN_THEN",
    "TOKEN_TRUE",
    "TOKEN_VAR",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_MUL",
    "TOKEN_DIV",
    "TOKEN_EQ",
    "TOKEN_IDENTIFIER",
    "TOKEN_INTEGER",
    "TOKEN_DOUBLE",
    "TOKEN_STRING",
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


const Keyword guttural_keywords[] = {
    { "else",     4 },
    { "elseif",   6 },
    { "end",      3 },
    { "false",    5 },
    { "function", 8 },
    { "if",       2 },
    { "return",   6 },
    { "then",     4 },
    { "true",     4 },
    { "var",      3 },
};


#define KeywordCount (sizeof(guttural_keywords) / sizeof(char *))

#define SetToken(lexer, token_type, start_ptr, line, len) \
    { \
        GutToken * t = &(lexer)->token; \
        t->type = (token_type); \
        t->start = (start_ptr); \
        t->linenumber = (line); \
        t->length = (len); \
    }

#define SetTokenType(lexer, token_type) (lexer)->token.type = (token_type)

#define SetInteger(lexer, number) (lexer)->token.value.value.integer = (number)
#define SetDouble(lexer, number) (lexer)->token.value.value.real = (number)

#define SetLookahead(lexer, gut_type) (lexer)->lookahead.type = (gut_type)


internal void lex (GutLexerState * lexer);


void GutLexerInit (GutState * state)
{
    GutLexerState * lexer = state->lexer;
    static int v;

    lexer->state = state;

    lexer->position = 0;
    lexer->colnumber = 0;
    lexer->linenumber = 0;

    SetTokenType(lexer, TOKEN_EOF);
    SetLookahead(lexer, TOKEN_EOF);

    lexer->input = NULL;
}


UInt32 GutLexerNext (GutLexerState * lexer)
{
    if (lexer->lookahead.type != TOKEN_EOF)
    {
        lexer->token = lexer->lookahead;
        SetLookahead(lexer, TOKEN_EOF);

        return lexer->token.type;
    }

    lex(lexer);

    return lexer->token.type;
}


UInt32 GutLexerPeek (GutLexerState * lexer)
{
    GutToken token = lexer->token;
    lex(lexer);
    lexer->lookahead = lexer->token;
    lexer->token = token;

    return lexer->lookahead.type;
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

#define HashString(state, gut_string) (state)->global_state->string_table->hash(gut_string)
#define GlobalStringTable(state) (state)->global_state->string_table


internal Bool32 CompareKeyword (char * start, char * end, const char * keyword)
{
    Size length = (end - start);

    if (strlen(keyword) != length) { return 0; }

    for (UInt32 i = 0; i < length; i++)
    {
        if (*(start + i) != *(keyword + i)) { return 0; }
    }

    return 1;
}


internal void lexIdentifier (GutLexerState * lexer)
{
    char * start = &Curr(lexer);
    Int32 linenumber = lexer->linenumber;

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
    Size length = end - start;

    GutTValue * string = GutStringNew(start, length);

    UInt32 hash = HashString(lexer->state, string);

    UInt32 token_type = TOKEN_IDENTIFIER;
    GutTableNode * maybe = GutTableHashGetPair(GlobalStringTable(lexer->state), hash);

    if (IsInteger(&maybe->value)) {
        token_type = TOKEN_ELSE + (UInt32)Integer(&maybe->value);
    }

    SetToken(lexer, token_type, start, linenumber, length);
}


#define StringToInteger(start, out_parse_end) strtol(start, &(out_parse_end), 10);
#define StringToDouble(start, out_parse_end) strtod(start, &(out_parse_end))


internal void lexNumber (GutLexerState * lexer)
{
    char * start = &Curr(lexer);
    char * parse_end;
    UInt32 token_type = TOKEN_INTEGER;

    while (IsDigit(Curr(lexer)))
    {
        Next(lexer);
    }

    if (Curr(lexer) == '.')
    {
        Next(lexer);

        while (IsDigit(Curr(lexer)))
        {
            Next(lexer);
        }

        token_type = TOKEN_DOUBLE;
    }

    if (token_type == TOKEN_INTEGER)
    {
        Int64 i = StringToInteger(start, parse_end);

        SetInteger(lexer, i);
    }
    else
    {
        Real64 r = StringToDouble(start, parse_end);

        SetDouble(lexer, r);
    }

    SetToken(lexer, token_type, start, lexer->linenumber, parse_end - start);
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
                char * delimiter = &c;
                UInt32 linenumber = lexer->linenumber;
                Next(lexer);

                while (Curr(lexer) != *delimiter)
                {
                    Next(lexer);
                }

                char * end = lexer->input + lexer->position;

                SetToken(lexer, TOKEN_STRING, delimiter + 1, linenumber, end - delimiter);
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
                SetTokenType(lexer, TOKEN_MUL);
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
