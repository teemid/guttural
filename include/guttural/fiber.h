#ifndef GUTTURAL_FIBER_H
#define GUTTURAL_FIBER_H

#include "guttural/common.h"


namespace guttural
{
    typedef struct
    {
        std::unique_ptr<Int32> bytecode;
    } Fiber;
}


#endif
