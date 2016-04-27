#ifndef GUTTURAL_COMMON_H
#define GUTTURAL_COMMON_H

#define internal static
#define persist static

#ifdef _WIN32
#define Assert(statement) \
            if (!(statement)) \
            { \
                printf("%s (%s: %d)\n", #statement, __FILE__, __LINE__); \
                abort(); \
            } \
            else { }
#endif

#endif
