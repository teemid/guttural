#ifndef GUTTURAL_H
#define GUTTURAL_H


#include "gut_object.h"


struct GutturalState;
typedef struct GutturalState GutState;

typedef void (*GutCFunction) (GutState * state);

GutState * GutNewState (void);

void GutDoFile (GutState * state, char * filename);

void GutPushNil     (GutState * state);
void GutPushInteger (GutState * state, Int64 i);
void GutPushDouble  (GutState * state, Real64 d);
void GutPushBoolean (GutState * state, Bool32 b);

GutTValue GutPop (GutState * state);

void GutRegister(GutState * state, GutCFunction function);


#endif
