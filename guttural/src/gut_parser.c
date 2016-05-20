#include <stdio.h>

#include "guttural.h"
#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_opcodes.h"
#include "gut_parser.h"


internal void Expression (GutState * state);


void GutParse (GutState * state)
{
    Expression(state);
}


internal void UnaryOperator   (GutState * state);
internal void Literal         (GutState * state);
internal void InfixOperator   (GutState * state);
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
    /* TOKEN_LET            */ UNUSED,
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


#define PrintToken(token_type) printf("%s\n", guttural_tokens[(token_type)])

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


internal void Literal (GutState * state)
{
    PrintToken(Current(state));
    // Emit constant value and so on.
}


internal void UnaryOperator (GutState * state)
{
    PrintToken(Current(state));
}


internal void InfixOperator (GutState * state)
{
    PrintToken(Current(state));
    GrammarRule * rule = GetRule(Current(state));

    ParsePrecedence(state, rule->precedence);
}


internal void Expression (GutState * state)
{
    ParsePrecedence(state, PRECEDENCE_LOWEST);
}


internal void ParsePrecedence (GutState * state, Precedence precedence)
{
    GrammarRule * left = GetRule(Next(state));

    Assert(left->prefix, "Expected an expression.");

    left->prefix(state);

    GrammarRule * operator = GetRule(Next(state));

    while (precedence < operator->precedence) {
        Assert(operator->infix, "Expected an operator");

        operator->infix(state);

        operator = GetRule(Next(state));
    }
}
