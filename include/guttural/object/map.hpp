#ifndef GUTTURAL_MAP_H
#define GUTTURAL_MAP_H

#include "guttural/object.hpp"


namespace Guttural
{
    struct Value;

    class Map final : public Object
    {
    public:
        Map (void);
        ~Map (void);

        uint32_t Add (Value key, Value value);
        uint32_t Remove (Value key);
    private:
        Value * keys;
        Value * values;
        size_t capacity;
        size_t count;
    };
}

#endif
