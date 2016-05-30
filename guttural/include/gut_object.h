#ifndef GUTTURAL_OBJECT_H
#define GUTTURAL_OBJECT_H


#include "gut_types.h"


// NOTE (Emil): Forward declare all the objects need for the value definiton.
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
    TYPE_KEYWORD,
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


#define MakeNil(tagged)  Type(tagged) = TYPE_NIL

#define Type(tagged)    (tagged)->type

#define Array(tagged)   (tagged)->value.array
#define Double(tagged)  (tagged)->value.real
#define Integer(tagged) (tagged)->value.integer
#define String(tagged)  (tagged)->value.string
#define Table(tagged)   (tagged)->value.table


#define IsArray(tagged)   Type(tagged) == TYPE_ARRAY
#define IsDouble(tagged)  Type(tagged) == TYPE_DOUBLE
#define IsInteger(tagged) Type(tagged) == TYPE_INTEGER
#define IsString(tagged)  Type(tagged) == TYPE_STRING
#define IsTable(tagged)   Type(tagged) == TYPE_TABLE
#define IsNil(tagged)     Type(tagged) == TYPE_NIL


#endif
