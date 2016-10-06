#ifndef GUTTURAL_LEXER_H
#define GUTTURAL_LEXER_H


namespace guttural
{
    class FileReader;

    enum class Kind
    {
        FUNCTION,
        RETURN,
        IF,
        THEN,
        WHILE,
        DO,
        END,
        COMMA,
        PERIOD,
        EOF
    };

    /*
     *  NOTE (Emil): With a streaming reader maybe this should not be pointing directly into source.
     */
    typedef struct
    {
        Kind kind;
        char * start;
    } Token;

    class Lexer
    {
    public:
        Lexer ();
        ~Lexer ();

        Kind Next (void);
        Kind Peek (void);
    private:
        FileReader * reader;

        Token current;
        Token lookahead;
    };
}

#endif
