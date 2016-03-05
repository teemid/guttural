#ifndef GUTTURAL_OBJECT_H
#define GUTTURAL_OBJECT_H

typedef struct GutturalArray GutturalArray;

typedef enum GutturalType
{
    ARRAY,
    NUMBER,
    DOUBLE,
    STRING
} GutturalType;

typedef union GutturalValue
{
    int i;
    double d;
    char * string;
    GutturalArray * array;
} GutturalValue;

typedef struct GutturalTaggedValue
{
    GutturalValue value;
    GutturalType type;
} GutturalTaggedValue;


#endif
