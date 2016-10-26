#ifndef GUTTURAL_LIST_H
#define GUTTURAL_LIST_H

#include <memory>

#include "guttural/object.hpp"


namespace Guttural
{
    struct Value;

    class List final : public Object
    {
    public:
        List (void);
        ~List (void);
    private:
        Value * buffer;
        size_t capacity;
        size_t count;
    };
}

#endif
