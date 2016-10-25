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

    struct Value
    {
        UValue value;
        ValueType type;
    };
}

#endif
