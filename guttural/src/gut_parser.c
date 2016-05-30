#include <stdio.h>
#include <stdarg.h>

#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_opcodes.h"
#include "gut_parser.h"
#include "gut_string.h"
#include "guttural.h"


internal void Statements (GutState * state);


void GutParse (GutState * state)
{
    Statements(state);
}


internal void Expression          (GutState * state);
internal void InfixOperator       (GutState * state);
internal void Literal             (GutState * state);
internal void Statement           (GutState * state);
internal void UnaryOperator       (GutState * state);
internal void VarStatement        (GutState * state);


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
    /* TOKEN_RETURN         */ UNUSED,
    /* TOKEN_THEN           */ UNUSED,
    /* TOKEN_TRUE           */ UNUSED,
    /* TOKEN_VAR            */ PREFIX(VarStatement),
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


#define PrintToken(state) printf("%s on %i\n", guttural_tokens[Current(state)], __LINE__)

#define GetRule(token_type) &rules[(token_type)]
#define Prefix(token_type)  rules[(token_type)].prefix
#define Infix(token_type)   rules[(token_type)].infix

#define Current(state)   (state)->lexer->token.type
#define Lookahead(state) (state)->lexer->lookahead.type

#define Next(state) GutLexerNext((state)->lexer)
#define Peek(state) GutLexerPeek((state)->lexer)

#define Expect(token, token_type) Assert((token) == (token_type))
#define IsType(token, token_type) ((token).type == (token_type))

#define Function(state) (state)->function

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


internal void Statements (GutState * state)
{
    Next(state);

    while (Current(state) != TOKEN_EOF)
    {
        Statement(state);
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

    Next(state);

    ParsePrecedence(state, rule->precedence);
}


internal void Expression (GutState * state)
{
    ParsePrecedence(state, PRECEDENCE_LOWEST);
}


#define NewInteger(variable_name, i) GutTValue variable_name = {}; Type(variable_name) = TYPE_INTEGER; Integer(variable_name) = (i);


internal UInt8 AddLocalVariable (GutState * state)
{
    GutFunction * current = Function(state);
    GutTValue tagged_string, local_variable;

    String(&tagged_string) = (GutString *)(&state->lexer->token.value);
    Type(&tagged_string) = TYPE_STRING;

    Type(&local_variable) = TYPE_INTEGER;
    Integer(&local_variable) = (current->variables->count - 1);
    // NewInteger(local_variable, function->variables->count - 1);

    GutTableHashAdd(current->variables, String(&tagged_string)->hash, &tagged_string, &local_variable);

    return (UInt8)Integer(&local_variable);
}


internal UInt8 AddLiteral (GutState * state)
{
    GutFunction * current = Function(state);
    GutTValue literal = state->lexer->token.value;

    GutArrayPush(current->constants, &literal);

    return (UInt8)current->constants->count - 1;
}


#define Emit(fn, op, n) n;


internal void VarStatement (GutState * state)
{
    PrintToken(state);
    // Match(state, TOKEN_LET, "Expected at let statement");

    Next(state);

    Match(state, TOKEN_IDENTIFIER, "Expected identifier");

    UInt8 local = AddLocalVariable(state);

    if (Next(state) == TOKEN_EQ)
    {
        Next(state);

        ParsePrecedence(state, PRECEDENCE_LOWEST);

        Emit(state->function, OP_LOAD_LOCAL, local);
    }

    if (Current(state) == TOKEN_COMMA)
    {
        GrammarRule * rule = GetRule(Next(state));

        Assert(rule->infix, "Expected comma");

        rule->prefix(state);
    }
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
