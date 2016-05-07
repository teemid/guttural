#ifndef GUTTURAL_HASHMAP_H
#define GUTTURAL_HASHMAP_H


#include "gut_object.h"


typedef struct GutturalHashTableNode
{
    UInt32 hash;
    GutTValue key;
    GutTValue value;
} GutTableNode;


typedef struct GutturalHashTable
{
    size_t capacity;
    size_t count;
    GutTableNode * nodes;
} GutTable;


GutTable *  GutTableNew    (size_t capacity);
void        GutTableResize (GutTable * table, size_t new_capacity);
void        GutTableDelete (GutTable * table);

void        GutTableAdd    (GutTable * table, GutTValue * key, GutTValue * value);
GutTValue * GutTableGet    (GutTable * table, GutTValue * key);
GutTValue * GutTableRemove (GutTable * table, GutTValue * key);


#endif
