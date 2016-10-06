#ifndef GUTTURAL_TABLE_H
#define GUTTURAL_TABLE_H


namespace guttural
{
    typedef struct Value;

    class Table
    {
    public:
        Table (void);
        ~Table (void);

        Value Find (Value key);
        void  Add (Value key, Value value);
        Value Remove (Value key);
    private:
        typedef struct
        {
            Value value;
        } Key;

        std::unique_ptr<Key> keys;
        std::unique_ptr<Value> values;
    };
}

#endif
