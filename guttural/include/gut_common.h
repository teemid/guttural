#ifndef GUTTURAL_COMMON_H
#define GUTTURAL_COMMON_H


#include <stdlib.h>


#define internal static
#define persist static

#define UNUSED(arg) (void)(arg)

#define Assert(statement, message) \
            if (!(statement)) \
            { \
                printf("%s (%s: %d)\n %s\n", #statement, __FILE__, __LINE__, message); \
                abort(); \
            } \
            else { }


#endif
