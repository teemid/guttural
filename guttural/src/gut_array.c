#include "gut_array.h"
#include "gut_memory.h"


#define Increment(variable) (variable) += 1
#define Decrement(variable) (variable) -= 1

#define CheckArraySize(array) \
    if (array->size == array->length) \
    { \
        array->data = (GutTValue *)REALLOC(array->data, array->size * 2); \
    }


void GutArrayInit (GutArray * array)
{
    array->data = (GutTValue *)MALLOC(DEFAULT_INITIAL_ARRAY_SIZE);
    array->size = DEFAULT_INITIAL_ARRAY_SIZE;
    array->length = 0;
}


void GutArrayPush (GutArray * array, GutTValue value)
{
    CheckArraySize(array)
    *(array->data + array->length) = value;
    Increment(array->length);
}


void GutArrayInser (GutArray * array, GutTValue value, UInt32 position)
{
    MOVE(array->data + position, array->data + (position + 1), array->length - position);
}

GutTValue GutArrayPop (GutArray * array)
{
    Decrement(array->length);

    return *(array->data + array->length);
}


GutTValue GutArrayRemove (GutArray * array, UInt32 position)
{
    GutTValue value = *(array->data + position);
    MOVE(array->data + (position + 1), array->data + position, array->length - position);

    return value;
}
