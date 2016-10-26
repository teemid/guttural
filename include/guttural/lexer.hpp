#ifndef GUTTURAL_LEXER_HPP
#define GUTTURAL_LEXER_HPP

#include <cstdint>

#include "guttural/util/source_reader.hpp"


namespace Guttural
{
    enum class Kind
    {
        #define GUTTURAL_TOKEN(token) token,
        #include "guttural/definitions/tokens.def"
    };

    union Value
    {
        double real;
        int64_t integer;
    };

    struct Token
    {
        Kind kind;
        Value value;
        char * start;
        size_t length;

        Token (void) : kind(Kind::EndOfFile), start(nullptr), length(0) { };
    };

    class Lexer
    {
    public:
        Lexer (void);
        explicit Lexer (SourceReader * reader);

        ~Lexer (void);

        Kind Next (void);
        Kind Peek (void);

        Token current;
        Token lookahead;
    private:
        Token Lex (void);

        SourceReader * reader;
        size_t line;
        size_t column;
    };
}

#endif
