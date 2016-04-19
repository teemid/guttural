#include "gut_conf.h"
#include "gut_error.h"
#include "gut_messages.h"
#include "gut_lexer.h"
#include "gut_parser.h"


void GutParserInit (GutState * state, GutIOStream * stream, )
{
    GutLexState lexer;
    lexer.state = state;

    GutLexerSetInput(&lexer, stream, );
}

#define CFuncCount(lex_state) \
    (lex_state)->state.c_function_count


#define EnterBlock(lex_state) \
    if (CFuncCount(lex_state) > GUTTURAL_MAX_C_FUNCTION_CALLS) { \
        GutError(GUT_C_FUNC_EXCEEDS_MAX) \
    } \

#define LeaveBlock(lex_state) \
    --CFuncCount(lex_state)


static void Scope (GutLexState * lex_state)
{
    EnterScope(lex_state);

    LeaveScope(lex_state);
}

static void Statement (GutLexState * state)
{

}


static void Parse (GutParserState * state)
{

}

static void ParseExpression (GutParserState * state)
{

}

static void ParseReserved (GutParserState * state)
{

}

static void ParseNumber (GutParserState * state)
{

}

static void ParseString (GutParserState * state)
{

}

