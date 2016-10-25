#ifndef GUTTURAL_FILE_READER_H
#define GUTTURAL_FILE_READER_H


namespace Guttural
{
    class FileReader
    {
    public:
        FileReader (void);
        ~FileReader (void);

        char * Next (void);
    };
}

#endif
