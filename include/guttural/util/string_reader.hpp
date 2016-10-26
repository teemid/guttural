#ifndef GUTTURAL_UTIL_STRING_READER_HPP
#define GUTTURAL_UTIL_STRING_READER_HPP

#include "guttural/util/source_reader.hpp"


namespace Guttural
{
    class StringReader : public SourceReader
    {
    public:
        explicit StringReader (char * string);
        StringReader(char * string, size_t length);
        ~StringReader (void);

        char * Next (void);
    private:
        char * input;
        char * current;
        char * end;
    };
}

#endif