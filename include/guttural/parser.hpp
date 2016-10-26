#ifndef GUTTURAL_PARSER_HPP
#define GUTTURAL_PARSER_HPP

namespace Guttural
{
    class Lexer;
    struct Fiber;

    class Parser
    {
    public:
        Parser (void);

        void parse (Lexer * lexer, Fiber * fiber);
    };
}

#endif