#ifndef GUTTURAL_LIST_H
#define GUTTURAL_LIST_H

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
        std::unique_ptr<Value> buffer;
        size_t capacity;
        size_t count;
    };
}

#endif
