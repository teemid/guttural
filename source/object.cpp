#include "guttural/object.hpp"


namespace Guttural
{
    Object::Object (void)
    {
        next = nullptr;
        prev = nullptr;
    }

    uint32_t Object::Hash (void)
    {
        return 0; // TODO (Emil): Fallback hashing method?
    }
}
