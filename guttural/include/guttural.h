#ifndef GUTTURAL_H
#define GUTTURAL_H


#include "gut_object.h"


struct GutturalState;
typedef struct GutturalState GutState;

typedef void (*GutCFunction) (GutState * state);

GutState * GutNewState (void);

void GutDoFile (GutState * state, char * filename);


void GutPush (GutState * state, GutValue value, GutType type);

#define GutPushNil(state)         GutPush(state, nil, TYPE_NIL)
#define GutPushInteger(state, value)  GutValue v; v.i = (value); GutPush(state, v, TYPE_INTEGER)
#define GutPushDouble(state, value)   GutValue v; v.d = (value); GutPush(state, v, TYPE_DOUBLE)
#define GutPushBoolean(state, value)  GutValue v; v.b = (value); GutPush(state, v, TYPE_BOOLEAN)


GutTValue GutPop (GutState * state);

void GutRegister(GutState * state, GutCFunction function);


#endif
