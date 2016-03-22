#ifndef GUTTURAL_HASHMAP_H
#define GUTTURAL_HASHMAP_H


#include "gut_object.h"


typedef struct GutturalHashTableNode
{
    UInt32 hash;
    void * key;
    GutTValue value;
} GutTableNode;


typedef struct GutturalHashTable
{
    GutArray * nodes;
} GutTable;


void      GutTableAdd    (GutTable * table, void * key, GutTValue value);
GutTValue GutTableRemove (GutTable * table, void * key);

#endif
