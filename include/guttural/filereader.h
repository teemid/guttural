#ifndef GUTTURAL_FILE_READER_H
#define GUTTURAL_FILE_READER_H

#include "guttural/common.h"


namespace guttural
{
    class FileReader
    {
    public:
        FileReader ();
        ~FileReader ();

        char Next(void);
    private:
        std::unique_ptr<char> filename;
        std::unique_ptr<char> source;
    };
}

#endif
