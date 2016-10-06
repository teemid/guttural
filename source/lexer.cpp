#include "guttural/lexer.h"
#include "guttural/filereader.h"


namespace guttural
{
    Lexer::Lexer (void) { }

    Lexer::~Lexer (void) { }

    Kind Lexer::Next (void)
    {
        return Kind::Function;
    }

    Kind Lexer::Peek (void)
    {
        return Kind::Function;
    }

    Token Lexer::Lex (void)
    {
        Token token;
        char c = reader->Next();

        switch (c)
        {
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
            case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
            case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z': case '_':
            {
                Size length = 1;
                while ('a' <= c && c <= 'z' || c == '_')
                {
                    c = reader->Next();
                }

                token.length = length;

                return token;
            }
            default:
            {
                Assert(false, "Lexer got illegal token.\n");
            }
        }
    }
}
