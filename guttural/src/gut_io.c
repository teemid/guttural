#include <stdio.h>

#include "gut_io.h"
#include "gut_types.h"

#define CFile(file) file->file



void GutFileOpen (GutFile * file, char * filename, char * mode)
{
    CFile(file) = fopen(filename, mode);

    if (file->file != NULL)
    {
        fseek(CFile(file), 0, SEEK_END);
        file->size = ftell(CFile(file));
        rewind(CFile(file));

        file->source = filename;
    }
}


void GutFileRead (GutFile * file, void * buffer, size_t size)
{
    size_t read = fread(buffer, size, sizeof(Byte), CFile(file));

    if (size != read)
    {
        printf("Asked for %d from %s, but could only read %d.", size, file->source, read);
        return;
    }
}


void GutFileClose (GutFile * file)
{
    fclose(CFile(file));
}
