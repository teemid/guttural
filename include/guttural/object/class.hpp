#ifndef GUTTURAL_OBJECT_CLASS_H
#define GUTTURAL_OBJECT_CLASS_H

#include "guttural/object.hpp"


namespace Guttural
{
    class String;

    class Klass final : public Object
    {
    public:
    private:
        String * name;
    };
}

#endif
