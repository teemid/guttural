#include "gut_parser.h"


static Parse (GutState * state, GutLexerState * lexer);


void GutParse (GutState * state, GutLexerState * lexer)
{
    Parse(state, lexer);
}


static Parse (GutState * state, GutLexerState * lexer)
{
    GutLexerNext(lexer);

    switch (lexer->token.type)
    {
        case TOKEN_LET:
        {

        } break;
        case TOKEN_IF:
        {

        } break;
    }
}


static ParseStatement (GutState * state, GutLexerState * lexer)
{

}


static ParseAssignment (GutState * state, GutLexerState * lexer)
{

}


static ParseDeclaration (GutState * state, GutLexerState * lexer)
{

}


static ParseIfStatement (GutState * state, GutLexerState * lexer)
{

}
