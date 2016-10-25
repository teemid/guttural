#ifndef GUTTURAL_LIST_H
#define GUTTURAL_LIST_H

#include "guttural/common.h"
#include "guttural/value.h"


namespace guttural
{
    class List
    {
        public:
            List (void);
            ~List (void);
        private:
            std::unique_ptr<TaggedValue> values;
            Size count;
            Size capacity;
    };
}


#endif
