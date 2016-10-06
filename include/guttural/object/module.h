#ifndef GUTTURAL_MODULE_H
#define GUTTURAL_MODULE_H

#include "guttural/common.h"


namespace guttural
{
    class Module
    {
    public:
        Module (void);
        ~Module (void);
    private:
        std::unique_ptr<char> name;
    };
}


#endif
