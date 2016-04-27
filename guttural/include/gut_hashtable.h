#ifndef GUTTURAL_HASHMAP_H
#define GUTTURAL_HASHMAP_H


#include "gut_object.h"


typedef struct GutturalHashTableNode
{
    struct GutturalHashTableNode * next;
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


GutTable * GutTableNew    (size_t size);
void       GutTableResize (GutTable * table, size_t new_size);
void       GutTableDelete (GutTable * table);

void       GutTableAdd    (GutTable * table, GutTValue * key, GutTValue value);
GutTValue  GutTableRemove (GutTable * table, GutTValue * key);

GutTValue  GutTableGet    (GutTable * table, GutTValue * key);


#endif
