#ifndef GUTTURAL_MEMORY_H
#define GUTTURAL_MEMORY_H

#include <stdlib.h>
#include <string.h>


#ifdef GUTTURAL_DEBUG

#define Allocate(type, bytes) (type)malloc(bytes)
#define Reallocate(type, memory, bytes) (type)realloc(memory, bytes)
#define Free(memory) free(memory)

#define Copy(source, destination, size) memcpy(destination, source, size)
#define Move(source, destination, size) memmove(destination, source, size)

#else

#define MALLOC(type, bytes)
#define REALLOC(type, memory, bytes)
#define CALLOC(type)

#endif

#endif
