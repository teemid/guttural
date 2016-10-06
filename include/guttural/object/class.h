#ifndef GUTTURAL_CLASS_H
#define GUTTURAL_CLASS_H

#include "guttural/common.h"


namespace guttural
{
    class Klass
    {
    public:
        Klass (void);
        ~Klass (void);
    private:
        std::unique_ptr<char> name;
    };
}

#endif
