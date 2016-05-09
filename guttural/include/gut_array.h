#ifndef GUTTURAL_ARRAY
#define GUTTURAL_ARRAY


#include "gut_object.h"


typedef struct GutturalArray
{
    GutTValue * elements;
    size_t capacity;
    size_t count;
} GutArray;


GutArray *  GutArrayNew    (size_t size);
void        GutArrayResize (GutArray * array, size_t size);
void        GutArrayDelete (GutArray * array);

void        GutArrayPush   (GutArray * array, GutTValue * value);
GutTValue   GutArrayPop    (GutArray * array);

GutTValue * GutArrayGet    (GutArray * array, UInt64 index);
void        GutArraySet    (GutArray * array, UInt64 index, GutTValue * value);
void        GutArrayInsert (GutArray * array, UInt64 index, GutTValue * value);


#endif
