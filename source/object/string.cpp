#include "guttural/object/string.hpp"
#include "guttural/util/hashing.hpp"


namespace Guttural
{
    String::String (void) { }

    uint32_t String::Hash (void)
    {
        return Hashing::djb2(c_str, length);
    }
}
