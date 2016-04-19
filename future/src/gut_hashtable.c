#include "gut_hashtable.h"
#include "gut_memory.h"

// typedef struct GutturalHashTableNode
// {
//     UInt32 hash;
//     void * key;
//     GutTValue value;
// } GutTableNode;


// typedef struct GutturalHashTable
// {
//     GutTableNode * nodes;
// } GutTable;

void GutTableInit (GutTable * table, size_t size)
{
    GutTable->nodes = MALLOC(GutTableNode *, size);
}

void GutTableAdd (GutTable * table, void * key, GutTValue value)
{
    GutTableNode * node = MALLOC(GutTableNode *, sizeof(GutTableNode));
    UInt32 hash = Hash(GutTValue);
}

GutTValue GutTableRemove (GutTable * table, void * key)
{

}

void GutTableResize (GutTable * table, size_t new_size)
{

}
