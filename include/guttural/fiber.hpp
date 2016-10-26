#ifndef GUTTURAL_FIBER_H
#define GUTTURAL_FIBER_H

#include <vector>

#include "guttural/common.hpp"
#include "guttural/object.hpp"


namespace Guttural
{
    class Module;

    struct Fiber
    {
        Object sentinel;
        std::vector<Module *> modules;
        std::unique_ptr<int32_t> bytecode;
    };
}


#endif
