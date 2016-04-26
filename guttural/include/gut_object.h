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
    Int64 i;
    Real64 d;
    char * string;
    GutArray * array;
    GutTable * table;
} GutValue;


typedef struct GutturalTaggedValue
{
    GutValue value;
    GutType type;
} GutTValue;

typedef GutTValue * StackPtr;


#define Integer(tagged) tagged.value.i
#define Double(tagged) tagged.value.d
#define Array(tagged) tagged.value->array
#define Table(tagged) tagged.value->table


#endif
