#ifndef GUTTURAL_LIST_H
#define GUTTURAL_LIST_H


namespace guttural
{
    typedef struct Value;

    class List
    {
        public:
            List (void);
            ~List (void);
        private:
            std::unqiue_ptr<Value> values;
            Size count;
            Size capacity;
    };
}


#endif
