#ifndef GUTTURAL_MAP_H
#define GUTTURAL_MAP_H

#include "guttural/object.hpp"


namespace Guttural
{
    class Map final : public Object
    {
    public:
        Map (void);
        ~Map (void);

        uint32_t Add (Value key, Value value);
        uint32_t Remove (Value key);
    private:
        std::unique_ptr<Value> keys;
        std::unique_ptr<Value> values;
        size_t capacity;
        size_t count;
    };
}

#endif
