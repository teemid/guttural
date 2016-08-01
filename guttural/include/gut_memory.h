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


#define GROWTH_FACTOR 2

#define Buffer(type, count) (type *)malloc(sizeof(type) * (count))
#define Grow(type, array, bytes) (type)realloc(array, bytes * GROWTH_FACTOR)


#else


#define Allocate(type, bytes)
#define Reallocate(type, memory, bytes)
#define Free(type)


#endif

#endif
