#ifndef GUTTURAL_INTERPRETER_HPP
#define GUTTURAL_INTERPRETER_HPP


namespace Guttural
{
    struct Fiber;

    class Interpreter
    {
    public:
        Interpreter (Fiber * fiber);
    private:
        Fiber * fiber;
    };
}

#endif
