#include "gut_array.h"
#include "gut_memory.h"


#define ARRAY_INITIAL_CAPACITY 12
#define ARRAY_GROWTH_RATE 2


#define GrowArray(array) GutArrayResize((array), (array)->capacity * ARRAY_GROWTH_RATE)


GutArray * GutArrayNew (size_t capacity)
{
    capacity = (capacity > 0) ? capacity : ARRAY_INITIAL_CAPACITY;

    GutArray * array = Allocate(GutArray *, sizeof(GutArray));
    array->elements = Allocate(GutTValue *, capacity * sizeof(GutTValue));
    array->capacity = capacity;
    array->count = 0;

    return array;
}


void GutArrayResize (GutArray * array, size_t capacity)
{
    array->elements = Reallocate(GutTValue *, array->elements, capacity * sizeof(GutTValue));
    array->capacity = capacity;
}


void GutArrayDelete (GutArray * array)
{
    Free(array->elements);
    Free(array);
}


void GutArrayPush (GutArray * array, GutTValue * value)
{
    array->elements[array->count++] = *value;

    if (array->count == array->capacity)
    {
        GrowArray(array);
    }
}


GutTValue GutArrayPop (GutArray * array)
{
    array->count--;

    return array->elements[array->count];
}


GutTValue * GutArrayGet (GutArray * array, UInt64 index)
{
    return &array->elements[index];
}


void GutArraySet (GutArray * array, UInt64 index, GutTValue * value)
{
    array->elements[index] = *value;
}
