#ifndef GUTTURAL_IO_H
#define GUTTURAL_IO_H


#include <stdio.h>


typedef struct GutturalFile
{
    FILE * file;
    size_t size;
    char * source;
} GutFile;


void GutFileOpen (GutFile * file, char * filename, char * mode);
void GutFileRead (GutFile * file, void * buffer, size_t bytes);
void GutFileClose (GutFile * file);


#endif
