#ifndef GUTTURAL_COMMON_H
#define GUTTURAL_COMMON_H


#include <stdlib.h>


#define internal static
#define persist static

#define Assert(statement) \
            if (!(statement)) \
            { \
                printf("%s (%s: %d)\n", #statement, __FILE__, __LINE__); \
                abort(); \
            } \
            else { }


#endif
