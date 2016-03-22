#ifndef GUTTURAL_ARRAY_H
#define GUTTURAL_ARRAY_H

#include "gut_object.h"


#define DEFAULT_INITIAL_ARRAY_SIZE 20

// NOTE (Emil): Each member is a tagged value, meaning an array is hetrogenous.
typedef struct GutturalArray
{
    GutTValue * data;
    UInt32 length;
    UInt32 size;
} GutArray;


#define Length(array_ptr) (array_ptr)->length

void      GutArrayInit   (GutArray * array);
void      GutArrayPush   (GutArray * array, GutTValue value);
GutTValue GutArrayPop    (GutArray * array);
void      GutArrayInsert (GutArray * array, GutTValue value, UInt32 position);
GutTValue GutArrayRemove (GutArray * array, UInt32 position);

#endif
