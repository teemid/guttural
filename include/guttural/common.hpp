#ifndef GUTTURAL_COMMON_H
#define GUTTURAL_COMMON_H

#include <cstdio>
#include <cstdint>
#include <memory>


#define UNUSED(var) (void)(var)

#define Assert(expression, message, ...) \
    if (!expression) \
    { \
        printf("Assertion: %s failed in %s at %i.\n", #expression, __FILE__, __LINE__); \
        printf(message, __VA_ARGS__); \
        \
        exit(1); \
    } \
    else \
    { \
        \
    }

#endif
