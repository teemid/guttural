#ifndef GUTTURAL_PARSER_H
#define GUTTURAL_PARSER_H


namespace guttural
{
    class Lexer;

    class Parser
    {
    public:
        Parser (void);
        ~Parser (void);
    private:
        Lexer * lexer;
    };
}

#endif
