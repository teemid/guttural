#include <stdio.h>
#include <stdarg.h>

#include "gut_common.h"
#include "gut_lexer.h"
#include "gut_opcodes.h"
#include "gut_parser.h"
#include "gut_string.h"
#include "guttural.h"


internal void Expression      (GutState * state);
internal void InfixOperator   (GutState * state);
internal void Literal         (GutState * state);
internal void Identifier      (GutState * state);
internal void Statement       (GutState * state);
internal void UnaryOperator   (GutState * state);
internal void VarStatement    (GutState * state);
internal void Assignment      (GutState * state, UByte local_variable);
internal void ParsePrecedence (GutState * state, Precedence precedence);


internal void Match           (GutState * state, UInt32 token_type, char *, ...);

#define NO_RULE                          { NULL,          NULL,          PRECEDENCE_NONE,  NULL }
#define PREFIX(function_ptr)             { function_ptr,  NULL,          PRECEDENCE_NONE,  NULL }
#define INFIX(precedence, function_ptr)  { NULL,          function_ptr,  precedence,       NULL }
#define PREFIX_OPERATOR(name)            { UnaryOperator, NULL,          PRECEDENCE_NONE,  name }
#define INFIX_OPERATOR(name, precedence) { NULL,          InfixOperator, precedence,       name }
#define OPERATOR(name)                   { UnaryOperator, InfixOperator, PRECEDENCE_TERM,  name }


GrammarRule rules[] = {
    /* TOKEN_ELSE           */ NO_RULE,
    /* TOKEN_ELSEIF         */ NO_RULE,
    /* TOKEN_END            */ NO_RULE,
    /* TOKEN_FALSE          */ NO_RULE,
    /* TOKEN_FUNCTION       */ NO_RULE,
    /* TOKEN_IF             */ NO_RULE,
    /* TOKEN_RETURN         */ NO_RULE,
    /* TOKEN_THEN           */ NO_RULE,
    /* TOKEN_TRUE           */ NO_RULE,
    /* TOKEN_VAR            */ PREFIX(VarStatement),
    /* TOKEN_PLUS           */ INFIX_OPERATOR("+", PRECEDENCE_TERM),
    /* TOKEN_MINUS          */ OPERATOR("-"),
    /* TOKEN_MUL            */ INFIX_OPERATOR("*", PRECEDENCE_FACTOR),
    /* TOKEN_DIV            */ INFIX_OPERATOR("/", PRECEDENCE_FACTOR),
    /* TOKEN_EQ             */ INFIX_OPERATOR("=", PRECEDENCE_ASSIGNMENT),
    /* TOKEN_IDENTIFIER     */ PREFIX(Identifier),
    /* TOKEN_INTEGER        */ PREFIX(Literal),
    /* TOKEN_DOUBLE         */ PREFIX(Literal),
    /* TOKEN_STRING         */ PREFIX(Literal),
    /* TOKEN_PAREN_OPEN     */ NO_RULE,
    /* TOKEN_PAREN_CLOSE    */ NO_RULE,
    /* TOKEN_SQUARE_OPEN    */ NO_RULE,
    /* TOKEN_SQUARE_CLOSE   */ NO_RULE,
    /* TOKEN_CURLY_OPEN     */ NO_RULE,
    /* TOKEN_CURLY_CLOSE    */ NO_RULE,
    /* TOKEN_PERIOD         */ NO_RULE,
    /* TOKEN_COMMA          */ NO_RULE,
    /* TOKEN_EOF            */ NO_RULE,
};


#define PrintToken(state) printf("%s on %i\n", guttural_tokens[Current(state)], __LINE__)

#define GetRule(token_type) &rules[(token_type)]
#define Prefix(token_type)  rules[(token_type)].prefix
#define Infix(token_type)   rules[(token_type)].infix

#define CurrentToken(state) (state)->lexer->token
#define LookaheadToken(state) (state)->lexer->lookahead

#define Current(state)   CurrentToken(state).type
#define Lookahead(state) LookaheadToken(state).type

#define Value(state) CurrentToken(state).value

#define Next(state) GutLexerNext((state)->lexer)
#define Peek(state) GutLexerPeek((state)->lexer)

#define Is(token, token_type) (token == (token_type))

#define Function(state) (state)->function

#define Precedence(token) *GetRule(token).precedence

#define NewInteger(variable_name, i) \
    GutTValue variable_name = {}; \
    Type(variable_name) = TYPE_INTEGER; \
    Integer(variable_name) = (i);

#define Emit(fn, op, n) n;


void GutParse (GutState * state)
{
    while (Next(state) != TOKEN_EOF)
    {
        ParsePrecedence(state, PRECEDENCE_LOWEST);
    }

    Match(state, TOKEN_EOF, "Expected TOKEN_EOF\n");

    PrintToken(state);
}


typedef struct {
    GutTable symbols;
} Function;


typedef struct {
    char * filename;
    UInt32 linenumber;
    GutTable * symbol;
    GutFunction * function;
} Prototype;


typedef struct {
    UInt32 start;
    UInt32 end;
} Jump;


typedef struct {
    // Current compiling function.
    Prototype * function_prototype;
    // Symbols defined in the current scope.
    GutTable symbols;

    GutState * state;
} Parser;


internal void Match (GutState * state, UInt32 token_type, char * message, ...)
{
    if (Current(state) != (Int32)token_type)
    {
        va_list arguments;

        va_start(arguments, message);

        vprintf(message, arguments);

        Assert(0, "Unexpected token\n");
    }
}

internal void Identifier (GutState * state)
{
    PrintToken(state);

    Peek(state);

    if (Is(Lookahead(state), TOKEN_PAREN_OPEN))
    {
        Next(state);

        PrintToken(state);

        Match(state, TOKEN_PAREN_OPEN, "Expected open paren.\n");

        do {
            Next(state);

            Expression(state);
        } while (Is(Next(state), TOKEN_COMMA));

        Match(state, TOKEN_PAREN_CLOSE, "Expected closing parentheses\n");

        PrintToken(state);
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


internal void CheckBuffer (void * buffer, UInt32 element_size, UInt32 size)
{
    UNUSED(buffer);
    UNUSED(element_size);
    UNUSED(size);
}


internal UInt8 AddLocalVariable (GutState * state)
{
    UNUSED(state);
}


internal UInt16 AddLiteral (GutState * state)
{
    GutFunction * function = Function(state);

    GutTValue literal = Value(state);

    GutArrayPush(function->constants, &literal);

    return (UInt16)function->constants->count - 1;
}


internal void Assignment (GutState * state, UByte local_variable)
{
    PrintToken(state);

    Next(state);

    Expression(state);

    Emit(state->function, OP_LOAD_LOCAL, local_variable);
}


internal void VarStatement (GutState * state)
{
    PrintToken(state); // Print TOKEN_VAR

    Next(state); // Next token

    PrintToken(state); // Print TOKEN_IDENTIFIER

    // Anything other than an identifier is an error
    Match(state, TOKEN_IDENTIFIER, "Expected identifier");

    // Add the identifier to the local variables.
    UByte local = 0; // AddLocalVariable(state);

    Next(state); // Next token

    // If the next token is TOKEN_EQ, do assignment.
    if (Is(Current(state), TOKEN_EQ))
    {
        Assignment(state, local);
    }
}


internal void Statement (GutState * state)
{
    GrammarFn prefix = Prefix(Current(state));

    Assert(prefix, "Expected statement");

    prefix(state);
}


internal void ParsePrecedence (GutState * state, Precedence precedence)
{
    GrammarFn prefix = Prefix(Current(state));

    Assert(prefix, "Expected an expression.");

    prefix(state);

    Peek(state);

    while (precedence < Precedence(Lookahead(state))) {
        GrammarFn infix = Infix(Next(state));

        Assert(infix, "Expected an operator");

        infix(state);
    }
}
