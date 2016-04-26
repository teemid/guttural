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
}

void GutTableAdd (GutTable * table, void * key, GutTValue value)
{
    GutTableNode * node = MALLOC(GutTableNode *, sizeof(GutTableNode));
}

GutTValue GutTableRemove (GutTable * table, void * key)
{
    GutTValue temp;
    Integer(temp) = 0;

    return temp;
}

void GutTableResize (GutTable * table, size_t new_size)
{

}
