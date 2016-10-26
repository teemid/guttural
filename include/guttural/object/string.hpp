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

        uint32_t Hash (void) override;
    private:
        char * c_str;
        uint32_t hash;
        size_t length;
    };
}

#endif
