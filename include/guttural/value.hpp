#ifndef GUTTURAL_VALUE_H
#define GUTTURAL_VALUE_H


namespace Guttural
{
    enum class ObjectType
    {
        Class,
        List,
        Map,
        Module,
    };

    class Klass;
    class List;
    class Map;
    class Module;

    union UObject
    {
        Klass * klass;
        List * list;
        Map * map;
        Module * module;
    };

    struct Object
    {
        UObject object;
        ObjectType type;
    };

    enum class ValueType
    {
        Double,
        Integer,
        Object,
    };

    union UValue
    {
        double real;
        int64_t integer;
        bool boolean;
        Object * object;
    };

    struct Value
    {
        UValue value;
        ValueType type;
    };
}

#endif
