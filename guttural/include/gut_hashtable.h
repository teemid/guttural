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
    Int32 size;
    Int32 in_use;
    GutTableNode * nodes;
} GutTable;


void      GutTableInit   (GutTable * table, size_t size);
void      GutTableAdd    (GutTable * table, void * key, GutTValue value);
GutTValue GutTableRemove (GutTable * table, void * key);
void      GutTableDelete (GutTable * table);

void GutTableResize (GutTable * table, UInt32 new_size);

#endif
