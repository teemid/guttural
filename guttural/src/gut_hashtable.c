#include "gut_conf.h"
#include "gut_common.h"
#include "gut_object.h"
#include "gut_string.h"
#include "gut_hashtable.h"
#include "gut_memory.h"


#define INVALID_HASH 0


internal UInt32 djb2(GutTValue * key)
{
    GutString * string = String(key);

    UInt32 hash = 5381;

    for (UInt64 i = 0; i < string->length; i++)
    {
        hash = ((hash << 5) + hash) + string->c_str[i]; /* hash * 33 + c */
    }

    return hash;
}


internal GutTableNode * AllocateNodes (size_t count)
{
    GutTableNode * nodes = Allocate(GutTableNode *, count * sizeof(GutTableNode));
    GutTableNode * node = NULL;

    for (UInt32 i = 0; i < count; i++)
    {
        node = &nodes[i];
        node->hash = INVALID_HASH;
        MakeNil(&node->key);
        MakeNil(&node->value);
    }

    return nodes;
}


internal void CheckCapacity (GutTable * table)
{
    Real64 usage = table->count / (Real64)table->capacity;

    if (usage > 0.7)
    {
        GutTableResize(table, table->capacity * 2);
    }
}


GutTable * GutTableNew (size_t capacity)
{
    capacity = (capacity > 0) ? capacity : INITIAL_TABLE_SIZE;

    GutTable * table = Allocate(GutTable *, sizeof(GutTable));
    table->nodes = AllocateNodes(capacity);
    table->capacity = capacity;
    table->count = 0;
    table->hash = djb2;

    return table;
}


void GutTableSetHashFunction (GutTable * table, HashFunction function_ptr)
{
    table->hash = function_ptr;
}


void GutTableResize (GutTable * table, size_t capacity)
{
    // NOTE (Emil): Save the old table while we move the nodes over.
    GutTableNode * old = table->nodes;
    UInt64 oldCapacity = table->capacity;

    // TODO (Emil): Handle allocation failure.
    table->nodes = AllocateNodes(capacity);
    table->capacity = capacity;

    GutTableNode * node = NULL;
    for (UInt32 i = 0; i < oldCapacity; i++)
    {
        node = &old[i];

        if (node->hash != INVALID_HASH)
        {
            table->nodes[node->hash % capacity] = *node;
        }
    }

    Free(old);
}


void GutTableDelete (GutTable * table)
{
    Free(table->nodes);
    Free(table);
}


void GutTableAdd (GutTable * table, GutTValue * key, GutTValue * value)
{
    UInt32 hash = table->hash(key);

    GutTableHashAdd(table, hash, key, value);
}


Bool32 GutTableExists (GutTable * table, GutTValue * key)
{
    UInt32 hash = table->hash(key);

    return GutTableHashExists (table, hash);
}


Bool32 GutTableHashExists (GutTable * table, UInt32 hash)
{
    UInt32 index = hash % table->capacity;

    return table->nodes[index].hash == hash;
}


GutTValue * GutTableGet (GutTable * table, GutTValue * key)
{
    UInt32 hash = table->hash(key);

    return GutTableHashGet(table, hash);
}


GutTValue * GutTableRemove (GutTable * table, GutTValue * key)
{
    UInt32 hash = table->hash(key);

    return GutTableHashRemove(table, hash);
}


void GutTableHashAdd (GutTable * table, UInt32 hash, GutTValue * key, GutTValue * value)
{
    UInt32 index = hash % table->capacity;
    GutTableNode * node = &table->nodes[index];

    UInt32 i = 1;
    while (node->hash != INVALID_HASH && node->hash != hash)
    {
        index = (hash + i * i) % table->capacity;
        node = &table->nodes[index];

        i += 1;
    }

    // NOTE (Emil): Don't count replacing a node.
    table->count = (node->hash == hash) ? table->count : table->count + 1;

    node->hash = hash;
    node->key = *key;
    node->value = *value;

    CheckCapacity(table);
}


GutTValue * GutTableHashGet (GutTable * table, UInt32 hash)
{
    UInt32 index = hash % table->capacity;

    GutTableNode * node = &table->nodes[index];

    UInt32 i = 1;
    while (node->hash != INVALID_HASH && node->hash != hash)
    {
        index = (hash + i * i) % table->capacity;
        node = &table->nodes[index];

        i += 1;
    }

    return &node->value;
}


GutTValue * GutTableHashRemove (GutTable * table, UInt32 hash)
{
    UInt32 index = hash % table->capacity;

    GutTableNode * node = &table->nodes[index];

    UInt32 i = 1;
    while (node->hash != hash)
    {
        index = (hash + i * i) % table->capacity;
        node = &table->nodes[index];

        i += 1;
    }

    table->count -= 1;

    node->hash = INVALID_HASH;
    MakeNil(&node->key);
    MakeNil(&node->value);

    return &node->value;
}


GutTableNode * GutTableGetPair (GutTable * table, GutTValue * key)
{
    UInt32 hash = table->hash(key);

    return GutTableHashGetPair(table, hash);
}

GutTableNode * GutTableHashGetPair (GutTable * table, UInt32 hash)
{
    UInt32 index = hash % table->capacity;

    GutTableNode * node = &table->nodes[index];

    UInt32 i = 1;
    while (node->hash != INVALID_HASH && node->hash != hash)
    {
        index = (hash + i * i) % table->capacity;
        node = &table->nodes[index];

        i += 1;
    }

    return node;
}
