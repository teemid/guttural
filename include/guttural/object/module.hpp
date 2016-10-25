#ifndef GUTTURAL_MODULE_H
#define GUTTURAL_MODULE_H

#include "guttural/object.hpp"


namespace Guttural
{
    class String;
    class Function;
    class Klass;
    struct Value;

    class Module final : public Object
    {
    public:
        Module (void);
    private:
        String * name;
        Value * variables;
        Value * constants;
        Function * functions;
        Klass * classes;
    };
}

#endif
