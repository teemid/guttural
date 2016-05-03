#include "gut_common.h"
#include "gut_object.h"
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


#define INVALID_HASH 0


internal UInt32 djb2(char * key, UInt32 length)
{
    UInt32 hash = 5381;

    for (UInt32 i = 0; i < length; i++)
    {
        hash = ((hash << 5) + hash) + key[i]; /* hash * 33 + c */
    }

    return hash;
}


internal UInt32 Hash(GutTValue * tagged)
{
    GutString * string = String(tagged);

    return djb2(string->c_str, string->length);
}


internal GutTableNode * NewNode (void)
{
    GutTableNode * node = Allocate(GutTableNode *, sizeof(GutTableNode));
    node->hash = INVALID_HASH;
    node->key = nil;
    node->next = NULL;

    return node;
}


GutTable * GutTableNew (size_t capacity)
{
    GutTable * table = Allocate(GutTable *, sizeof(GutTable));
    table->nodes = Allocate(GutTableNode *, capacity * sizeof(GutTableNode));
    table->capacity = capacity;
    table->count = 0;

    for (UInt32 i = 0; i < table->capacity; i++)
    {
        GutTableNode * node = &table->nodes[i];

        node->hash = INVALID_HASH;
        node->key = nil;
        node->next = NULL;
    }

    return table;
}


void GutTableResize (GutTable * table, size_t new_count)
{
    table->nodes = Allocate(GutTableNode *, new_count * sizeof(GutTableNode));
}


void GutTableDelete (GutTable * table)
{
    for (Int32 i = 0; i < table->capacity; i++)
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


GutTValue GutTableGet (GutTable * table, GutTValue key)
{
    UInt32 hash = Hash(&key);
    UInt32 index = hash % table->capacity;

    GutTableNode * node = &table->nodes[index];
    GutTValue value = node->value;

    return value;
}


void GutTableAdd (GutTable * table, GutTValue key, GutTValue value)
{
    UInt32 hash = Hash(&key);
    UInt32 index = hash % table->capacity;

    GutTableNode * node = &table->nodes[index];

    if (node->hash == INVALID_HASH)
    {
        node->hash = hash;
        node->key = key;
        node->value = value;
    }
    else
    {
        GutTableNode * chain = NewNode();
        chain->hash = hash;
        chain->key = key;
        chain->value = value;
    }
}


GutTValue GutTableRemove (GutTable * table, GutTValue key)
{
    UInt32 hash = Hash(&key);
    UInt32 index = hash % table->capacity;

    GutTableNode * node = &table->nodes[index];

    if (node->hash != hash)
    {
        while (node->next != NULL)
        {

        }
    }
    else
    {
        node->hash = INVALID_HASH;
    }

    return node->value;
}
