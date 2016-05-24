#ifndef GUTTURAL_HASHMAP_H
#define GUTTURAL_HASHMAP_H


#include "gut_object.h"
#include "gut_types.h"


typedef UInt32 (*HashFunction) (GutTValue * value);


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
    HashFunction hash;
} GutTable;


GutTable *  GutTableNew             (size_t capacity);
void        GutTableResize          (GutTable * table, size_t new_capacity);
void        GutTableDelete          (GutTable * table);
void        GutTableSetHashFunction (GutTable * table, HashFunction function_ptr);

void        GutTableAdd             (GutTable * table, GutTValue * key, GutTValue * value);
void        GutTableAddHash         (GutTable * table, GutTValue * key, UInt32 hash, GutTValue * value);

Bool32      GutTableHasKey          (GutTable * table, GutTValue * key);
Bool32      GutTableHasKeyHash      (GutTable * table, UInt32 hash);

GutTValue * GutTableGet             (GutTable * table, UInt32 hash);
GutTValue * GutTableRemove          (GutTable * table, UInt32 hash);

GutTValue * GutTableGetHash         (GutTable * table, GutTValue * key);
GutTValue * GutTableRemoveHash      (GutTable * table, GutTValue * key);


#endif
