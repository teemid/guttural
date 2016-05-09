#include <stdio.h>

#include "guttural.h"
#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_parser.h"


internal void Parse (GutState * state);


void GutParse (GutState * state)
{
    Parse(state);
}


#define Current(state)   (state)->lexer->token.type
#define Lookahead(state) (state)->lexer->lookahead.type
#define Semantics(state)   (state)->lexer->token.semantics

#define Next(state) GutLexerNext((state)->lexer)
#define Peek(state) GutLexerPeek((state)->lexer)

#define Expect(token, token_type) Assert((token) == (token_type))
#define IsType(token, token_type) ((token).type == (token_type))

#define IsOperator(type) ( \
    ((type) == TOKEN_PLUS) || ((type) == TOKEN_MINUS) || \
    ((type) == TOKEN_MUL) || ((type) == TOKEN_DIV))



internal void ParseDeclaration (GutState * state)
{

    Expect(Peek(state), TOKEN_IDENTIFIER);
}


/*
internal void ParseStatement (GutState * state)
{

}


internal void ParseAssignment (GutState * state)
{

}

internal void ParseIfStatement (GutState * state)
{

}


internal void ParseCall (GutState * state)
{

}

internal void ParseOperator (GutState * state)
{

}

internal void ParseFunctionDeclaration (GutState * state)
{

}


static Int32 operator_precedence[] = {
    0, // TOKEN_PLUS
    0, // TOKEN_MINUS
    1, // TOKEN_MUL
    1, // TOKEN_DIV
    2, // TOKEN_EQ
};


#define Precedence(operator) operator_precedence[(operator) - LAST_RESERVED]
*/


internal void Parse (GutState * state)
{
    while (1)
    {
        UInt32 type = Next(state);

        switch (type)
        {
            case TOKEN_INTEGER:
            case TOKEN_DOUBLE:
            {
                printf("%s: %lld \n", guttural_tokens[type], Semantics(state).integer);

                if (IsOperator(Peek(state)))
                {
                    GutPushInteger(state, Semantics(state).integer);
                }
            } break;
            case TOKEN_LET:
            {
                ParseDeclaration(state);
            } break;
            case TOKEN_EOF:
            {
                return;
            } break;
            default:
            {
                printf("%s\n", guttural_tokens[type]);
            } break;
        }
    }
}
