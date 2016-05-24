#ifndef GUTTURAL_OBJECT_H
#define GUTTURAL_OBJECT_H


#include "gut_types.h"


typedef struct GutturalArray GutArray;
typedef struct GutturalHashTable GutTable;
typedef struct GutturalString GutString;

// Size of enum is compiler dependent?
// Size of members equals sizeof(int)
typedef enum GutturalType
{
    TYPE_ARRAY,
    TYPE_DOUBLE,
    TYPE_INTEGER,
    TYPE_NIL,
    TYPE_STRING,
    TYPE_TABLE,
} GutType;


extern char const * const guttural_types[];


typedef union GutturalValue
{
    Int64 integer;
    Real64 real;
    GutString * string;
    GutArray * array;
    GutTable * table;
} GutValue;


typedef struct GutturalTaggedValue
{
    GutValue value;
    GutType type;
} GutTValue;


typedef GutTValue * StackPtr;


extern GutTValue nil;


#define Type(tagged)    tagged->type

#define Integer(tagged) tagged->value.integer
#define Double(tagged)  tagged->value.real
#define String(tagged)  tagged->value.string
#define Array(tagged)   tagged->value.array
#define Table(tagged)   tagged->value.table


#endif
