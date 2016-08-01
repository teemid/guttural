#ifndef GUTTURAL_H
#define GUTTURAL_H


typedef struct GutturalState GutState;

typedef void (*GutCFunction) (GutState * state);


#define GUT_TYPE_INTEGER  0
#define GUT_TYPE_DOUBLE   1
#define GUT_TYPE_STRING   2
#define GUT_TYPE_BOOLEAN  3
#define GUT_TYPE_FUNCTION 4


GutState * GutNewState (void);

void GutDoFile (GutState * state, char * filename);

void GutPush(GutState * state, int type, void * value);


void GutRegister(GutState * state, GutCFunction function);


#endif
