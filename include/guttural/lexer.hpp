#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H


namespace Guttural
{
    class FileReader;

    class Lexer
    {
    public:
        Lexer (void);
        ~Lexer (void);
    private:
        FileReader * reader;
    };
}

#endif
