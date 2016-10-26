#include "guttural/util/hashing.hpp"


namespace Guttural
{
namespace Hashing
{
    uint32_t djb2 (char * string, size_t length)
    {
        unsigned int hash = 5381;

        for (size_t i = 0; i < length; i++)
        {
            hash = ((hash << 5) + hash) + string[i];
        }

        return hash;
    }
}
}