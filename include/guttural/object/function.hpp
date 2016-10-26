#ifndef GUTTURAL_FUNCTION_H
#define GUTTURAL_FUNCTION_H

#include "guttural/object.hpp"


namespace Guttural
{
    class String;
    struct Value;

    class Function final : public Object
    {
    public:
        Function (void);
        ~Function (void);
    private:
        String * name;
        Value * constants;
    };
}


#endif
