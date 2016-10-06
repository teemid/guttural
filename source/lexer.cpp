#include "guttural/lexer.h"


namespace guttural
{
    Lexer::Lexer (void) { }

    Lexer::~Lexer (void) { }

    Kind Lexer::Next (void)
    {
        return Kind::Function;
    }
}
