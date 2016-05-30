#ifndef GUTTURAL_STRING_H
#define GUTTURAL_STRING_H


#include "gut_types.h"
#include "gut_object.h"


typedef struct GutturalString
{
    char * c_str;
    size_t length;
    UInt32 hash;
} GutString;


GutTValue * GutStringNew     (char * string, Size length);
void        GutStringDelete  (GutTValue * string);

Size        GutStringLength  (GutTValue * string);
Bool32      GutStringCompare (GutTValue * s1, GutTValue * s2, Size length);

#endif
