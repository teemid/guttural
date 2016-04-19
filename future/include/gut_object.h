#ifndef GUTTURAL_OBJECT_H
#define GUTTURAL_OBJECT_H


#include "gut_types.h"


typedef struct GutturalArray GutArray;
typedef struct GutturalHashTable GutTable;

// Size of enum is compiler dependent?
// Size of members equals sizeof(int)
typedef enum GutturalType
{
    TYPE_ARRAY,
    TYPE_DOUBLE,
    TYPE_INTEGER,
    TYPE_STRING,
    TYPE_TABLE
} GutType;


typedef union GutturalValue
{
    Int32 i;
    Real64 d;
    char * string;
    GutArray * array;
    GutTable * table;
} GutValue;


typedef GutValue * StackPtr;


typedef struct GutturalTaggedValue
{
    GutValue value;
    GutType type;
} GutTValue;


#define Integer(value) value.i
#define Double(value) value.d
#define Array(value) value->array
#define Table(value) value->table


#endif