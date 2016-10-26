#include "guttural/util/file_reader.hpp"

#include <fstream>


namespace Guttural
{   
    static std::fstream * file;

    FileReader::FileReader (char * filename)
    {
        file = new std::fstream(filename);
    }

    FileReader::~FileReader (void)
    {
        delete file;
    }

    char * FileReader::Next (void)
    {
        static char c;
        file->get(c);
        
        return &c;
    }
}
