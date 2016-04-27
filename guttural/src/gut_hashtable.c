#include "gut_common.h"
#include "gut_hashtable.h"
#include "gut_memory.h"
#include "gut_types.h"

// typedef struct GutturalHashTableNode
// {
//     struct GutturalHashTableNode * node;
//     UInt32 hash;
//     void * key;
//     GutTValue value;
// } GutTableNode;


// typedef struct GutturalHashTable
// {
//     Int32 size;
//     Int32 in_use;
//     GutTableNode * nodes;
// } GutTable;

internal UInt32 BadHash (GutTValue * tagged)
{
    return 0;
}


#define Hash(tagged) BadHash(tagged)
#define NewNode() Allocate(GutTableNode *, sizeof(GutTableNode))


GutTable * GutTableNew (size_t count)
{
    GutTable * table = Allocate(GutTable *, sizeof(GutTable));
    table->nodes = Allocate(GutTableNode *, count * sizeof(GutTableNode));
    table->size = count;
    table->in_use = 0;

    for (UInt32 i = 0; i < table->size; i++)
    {
        GutTableNode * node = &table->nodes[i];

        node->next = NULL;
        node->key = NULL;
    }

    return table;
}


void GutTableResize (GutTable * table, size_t new_count)
{

}


void GutTableDelete (GutTable * table)
{
    for (Int32 i = 0; i < table->size; i++)
    {
        GutTableNode * node = &table->nodes[i];
        GutTableNode * next = node->next;
        GutTableNode * temp = NULL;

        while (next != NULL)
        {
            temp = next->next;
            Free(next);
            next = temp;
        }
    }

    Free(table->nodes);
    Free(table);
}


GutTValue GutTableGet (GutTable * table, GutTValue * key)
{
    UInt32 hash = Hash(key);
    UInt32 index = hash % table->size;

    GutTableNode * node = &table->nodes[index];
    GutTValue value = node->value;

    return value;
}


void GutTableAdd (GutTable * table, GutTValue * key, GutTValue value)
{
    UInt32 hash = Hash(key);
    UInt32 index = hash % table->size;

    GutTableNode * node = &table->nodes[index];

    if (node->key == NULL)
    {
        node->hash = hash;
        node->key = Allocate(void *, sizeof(key));
        node->key = key;
        node->value = value;
    }
    else
    {
        GutTableNode * node = NewNode();
    }
}


GutTValue GutTableRemove (GutTable * table, GutTValue * key)
{
    GutTValue temp;
    temp.value.i = 0;

    return temp;
}
