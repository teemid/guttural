#ifndef GUTTURAL_COMMON_H
#define GUTTURAL_COMMON_H

#include <cstdio>
#include <memory>
#include "guttural/types.h"


#define UNUSED(var) (void)(var)

#define Assert(expression, ...) \
    if (!expression) \
    { \
        printf("Assertion: %s failed in %s at %i.\n", #expression, __FILE__, __LINE__); \
        printf(__VA_ARGS__); \
        \
        exit(1); \
    } \
    else \
    { \
        \
    }

#endif
