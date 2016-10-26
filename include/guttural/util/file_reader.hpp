#ifndef GUTTURAL_FILE_READER_H
#define GUTTURAL_FILE_READER_H

#include "guttural/util/source_reader.hpp"
#include "guttural/common.hpp"


namespace Guttural
{
    class FileReader : public SourceReader
    {
    public:
        FileReader (char * filename);
        ~FileReader (void);

        char * Next (void);
    private:
        char * input;
        char * current;
    };
}

#endif
