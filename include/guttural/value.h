#ifndef GUTTURAL_VALUE_H
#define GUTTURAL_VALUE_H


namespace guttural
{
    // NOTE (Emil): Forward declarations of objects.
    class Klass;
    class List;
    class Module;
    class String;
    class Table;

    enum class ObjectType
    {
        List,
        Module,
        String,
        Table
    };

    typedef union
    {
        List * list;
        String * string;
        Table * table;
        Module * module;
    } Object;

    enum class Type
    {
        Real,
        Integer,
        Object
    };

    typedef union _Value
    {
        Object object;
        Real64 real;
        Int64  integer;
    } Value;

    typedef struct _TaggedValue
    {
        Type type;
        Value value;
    } TaggedValue;
}

#endif
