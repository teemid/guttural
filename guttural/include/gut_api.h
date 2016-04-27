#ifndef GUTTURAL_API_H
#define GUTTURAL_API_H

#include "gut_state.h"
#include "gut_object.h"

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
