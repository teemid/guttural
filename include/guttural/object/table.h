#ifndef GUTTURAL_TABLE_H
#define GUTTURAL_TABLE_H

#include "guttural/common.h"
#include "guttural/value.h"


namespace guttural
{
    class Table
    {
    public:
        Table (void);
        ~Table (void);

        TaggedValue Find   (TaggedValue key);
        void        Add    (Value key, TaggedValue tvalue);
        TaggedValue Remove (TaggedValue key);
    private:
        typedef struct
        {
            TaggedValue tvalue;
            Size index;
        } Key;

        std::unique_ptr<Key> keys;
        std::unique_ptr<TaggedValue> values;

        Size count;
        Size key_capacity;
        Size value_capacity;
    };
}

#endif
