#ifndef GUTTURAL_INTERPRETER_H
#define GUTTURAL_INTERPRETER_H


namespace guttural
{
    class Parser;

    class Interpreter
    {
    public:
        Interpreter (void);
        ~Interpreter (void);
    private:
        Parser * parser;
    };
}


#endif
