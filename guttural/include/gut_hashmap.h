#ifndef GUTTURAL_HASHMAP_H
#define GUTTURAL_HASHMAP_H


#include "gut_object.h"


typedef struct GutturalNode
{
    int hash;
    void * key;
    GutturalValue value;
} GutturalNode;


typedef struct GutturalHashmap
{
    GutturalNode * nodes;
} GutturalHashmap;


#endif
