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


Bool32      GutTableExists          (GutTable * table, GutTValue * key);
void        GutTableAdd             (GutTable * table, GutTValue * key, GutTValue * value);
GutTValue * GutTableGet             (GutTable * table, GutTValue * key);
GutTValue * GutTableRemove          (GutTable * table, GutTValue * key);


Bool32      GutTableHashExists      (GutTable * table, UInt32 hash);
void        GutTableHashAdd         (GutTable * table, UInt32 hash, GutTValue * key, GutTValue * value);
GutTValue * GutTableHashGet         (GutTable * table, UInt32 hash);
GutTValue * GutTableHashRemove      (GutTable * table, UInt32 hash);


GutTableNode * GutTableGetPair      (GutTable * table, GutTValue * key);
GutTableNode * GutTableHashGetPair  (GutTable * table, UInt32 hash);


#endif
