#ifndef GUTTURAL_MEMORY_H
#define GUTTURAL_MEMORY_H

#include <stdlib.h>
#include <string.h>


#ifdef GUTTURAL_DEBUG

#define MALLOC(bytes) malloc(bytes)
#define REALLOC(memory, bytes) realloc(memory, bytes)
#define CALLOC(type)
#define FREE(memory) free(memory)

#define COPY(source, destination, size) memcpy(destination, source, size)
#define MOVE(source, destination, size) memmove(destination, source, size)

#else

#define MALLOC(type, bytes)
#define REALLOC(type, memory, bytes)
#define CALLOC(type)

#endif

#endif
