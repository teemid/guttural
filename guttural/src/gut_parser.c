#include <stdio.h>
#include <stdarg.h>

#include "guttural.h"
#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_opcodes.h"
#include "gut_parser.h"


internal void Statements (GutState * state);


void GutParse (GutState * state)
{
    Statements(state);
}


internal void Statement           (GutState * state);
internal void LetStatement        (GutState * state);
internal void Expression          (GutState * state);
internal void UnaryOperator       (GutState * state);
internal void Literal             (GutState * state);
internal void InfixOperator       (GutState * state);


internal void ParsePrecedence (GutState * state, Precedence precedence);


#define UNUSED                           { NULL,          NULL,          PRECEDENCE_NONE,  NULL }
#define PREFIX(function_ptr)             { function_ptr,  NULL,          PRECEDENCE_NONE,  NULL }
#define INFIX(precedence, function_ptr)  { NULL,          function_ptr,  precedence,       NULL }
#define PREFIX_OPERATOR(name)            { UnaryOperator, NULL,          PRECEDENCE_NONE,  name }
#define INFIX_OPERATOR(name, precedence) { NULL,          InfixOperator, precedence,       name }
#define OPERATOR(name)                   { UnaryOperator, InfixOperator, PRECEDENCE_TERM,  name }


GrammarRule rules[] = {
    /* TOKEN_ELSE           */ UNUSED,
    /* TOKEN_ELSEIF         */ UNUSED,
    /* TOKEN_END            */ UNUSED,
    /* TOKEN_FALSE          */ UNUSED,
    /* TOKEN_FUNCTION       */ UNUSED,
    /* TOKEN_IF             */ UNUSED,
    /* TOKEN_LET            */ PREFIX(LetStatement),
    /* TOKEN_RETURN         */ UNUSED,
    /* TOKEN_THEN           */ UNUSED,
    /* TOKEN_TRUE           */ UNUSED,
    /* TOKEN_PLUS           */ INFIX_OPERATOR("+", PRECEDENCE_TERM),
    /* TOKEN_MINUS          */ OPERATOR("-"),
    /* TOKEN_MUL            */ INFIX_OPERATOR("*", PRECEDENCE_FACTOR),
    /* TOKEN_DIV            */ INFIX_OPERATOR("/", PRECEDENCE_FACTOR),
    /* TOKEN_EQ             */ INFIX_OPERATOR("=", PRECEDENCE_ASSIGNMENT),
    /* TOKEN_IDENTIFIER     */ UNUSED,
    /* TOKEN_INTEGER        */ PREFIX(Literal),
    /* TOKEN_DOUBLE         */ PREFIX(Literal),
    /* TOKEN_STRING         */ PREFIX(Literal),
    /* TOKEN_PAREN_OPEN     */ UNUSED,
    /* TOKEN_PAREN_CLOSE    */ UNUSED,
    /* TOKEN_SQUARE_OPEN    */ UNUSED,
    /* TOKEN_SQUARE_CLOSE   */ UNUSED,
    /* TOKEN_CURLY_OPEN     */ UNUSED,
    /* TOKEN_CURLY_CLOSE    */ UNUSED,
    /* TOKEN_PERIOD         */ UNUSED,
    /* TOKEN_COMMA          */ UNUSED,
    /* TOKEN_EOF            */ UNUSED,
};


#define PrintToken(state) printf("%s\n", guttural_tokens[Current(state)])

#define GetRule(token_type) &rules[(token_type)]
#define Prefix(token_type)  rules[(token_type)].prefix
#define Infix(token_type)   rules[(token_type)].infix

#define Current(state)   (state)->lexer->token.type
#define Lookahead(state) (state)->lexer->lookahead.type

#define Next(state) GutLexerNext((state)->lexer)
#define Peek(state) GutLexerPeek((state)->lexer)

#define Expect(token, token_type) Assert((token) == (token_type))
#define IsType(token, token_type) ((token).type == (token_type))


#define SetLiteral(state)


internal void Match (GutState * state, UInt32 token_type, char * message, ...)
{
    if (Current(state) != (Int32)token_type)
    {
        va_list arguments;

        va_start(arguments, message);

        vprintf(message, arguments);
    }
}


internal void Statements(GutState * state)
{
    Next(state);

    while (Current(state) != TOKEN_EOF)
    {
        PrintToken(state);

        Next(state);
    }
}


internal void Literal (GutState * state)
{
    PrintToken(state);
    // Emit constant value and so on.
}


internal void UnaryOperator (GutState * state)
{
    PrintToken(state);
}


internal void InfixOperator (GutState * state)
{
    PrintToken(state);
    GrammarRule * rule = GetRule(Current(state));

    ParsePrecedence(state, rule->precedence);
}


internal void Expression (GutState * state)
{
    ParsePrecedence(state, PRECEDENCE_LOWEST);
}


internal void AddLocalVariable (GutState * state)
{
    *state;
}


internal void LetStatement (GutState * state)
{
    PrintToken(state);
    // Match(state, TOKEN_LET, "Expected at let statement");

    Next(state);

    Match(state, TOKEN_IDENTIFIER, "Expected identifier");

    AddLocalVariable(state);
}


internal void Statement (GutState * state)
{
    GrammarRule * rule = GetRule(Current(state));

    Assert(rule->prefix, "Expected statement");

    rule->prefix(state);
}


internal void ParsePrecedence (GutState * state, Precedence precedence)
{
    GrammarRule * left = GetRule(Current(state));

    Assert(left->prefix, "Expected an expression.");

    left->prefix(state);

    GrammarRule * operator = GetRule(Next(state));

    while (precedence < operator->precedence) {
        Assert(operator->infix, "Expected an operator");

        operator->infix(state);

        operator = GetRule(Next(state));
    }
}
