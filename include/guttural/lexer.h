#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H

#include "guttural/common.h"


namespace guttural
{
    class FileReader;

    enum class Kind
    {
        Function
    };

    /*
     *  NOTE (Emil): With a streaming reader maybe this should not be pointing directly into source.
     */
    typedef struct
    {
        Real64 real;
        Int64 integer;
        char * string;
    } RawValue;

    typedef struct
    {
        Kind kind;
        RawValue value;
        Size length;
    } Token;

    class Lexer
    {
    public:
        Lexer ();
        ~Lexer ();

        Kind Next (void);
        Kind Peek (void);
    private:
        Token Lex (void);

        FileReader * reader;

        Token current;
        Token lookahead;
    };
}

#endif
