#ifndef GUTTURAL_ARRAY_H
#define GUTTURAL_ARRAY_H

#include "gut_object.h"


typedef struct GutturalArray
{
    GutturalValue * data;
    int length;
} GutturalArray;


#define guttural_array_length(array_ptr) (array_ptr)->length

void guttural_array_init (GutturalArray * array);
void guttural_array_push (GutturalArray * array, GutturalValue value);
void guttural_array_pop (GutturalArray * array);
void guttural_array_delete (GutturalArray * array);

#endif
