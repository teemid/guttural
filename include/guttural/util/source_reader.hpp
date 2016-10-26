#ifndef GUTTURAL_UTIL_SOURCE_READER_HPP
#define GUTTURAL_UTIL_SOURCE_READER_HPP


namespace Guttural
{
    class SourceReader
    {
    public:
        virtual ~SourceReader (void) { };

        virtual char * Next (void) = 0;
    };
}


#endif