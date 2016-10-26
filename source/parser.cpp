#include "guttural/parser.hpp"
#include "guttural/fiber.hpp"
#include "guttural/lexer.hpp"


namespace Guttural
{
    Parser::Parser (void) { }

    void Parser::parse (Lexer * lexer, Fiber * fiber)
    {
        UNUSED(lexer);
        UNUSED(fiber);
    }
}
