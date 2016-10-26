#ifndef GUTTURAL_UTIL_HASHING_HPP
#define GUTTURAL_UTIL_HASHING_HPP

#include <cstdint>

namespace Guttural
{
namespace Hashing
{
    uint32_t djb2 (char * string, size_t length);
}
}

#endif