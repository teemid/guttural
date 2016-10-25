#ifndef GUTTURAL_STRING_H
#define GUTTURAL_STRING_H

#include "guttural/object.hpp"


namespace Guttural
{
    class String final : public Object
    {
    public:
        String (void);
        explicit String (char * string);
        String (char * string, size_t length);

        Hash (void);
    private:
        char * c_str;
        size_t length;
    };
}

#endif
