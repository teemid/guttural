#ifndef GUTTURAL_OBJECT_H
#define GUTTURAL_OBJECT_H

#include <cstdint>


namespace Guttural
{
    class Object
    {
    public:
        Object (void);

        virtual uint32_t Hash (void);
    private:
        Object * next;
        Object * prev;
    };
}

#endif
