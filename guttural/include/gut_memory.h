#ifndef GUTTURAL_MEMORY_H
#define GUTTURAL_MEMORY_H

#include <stdlib.h>

#ifdef GUTTURAL_DEBUG

#define MALLOC(type, bytes) (type)malloc(bytes)
#define REALLOC(type, memory, bytes) (type)realloc(memory, bytes)
#define CALLOC(type)
#define FREE(memory) free(memory)

#else

#define MALLOC(type, bytes)
#define REALLOC(type, memory, bytes)
#define CALLOC(type)

#endif

#endif
