#ifndef GUTTURAL_CORE_H
#define GUTTURAL_CORE_H


#include "gut_state.h"


void GutCoreInitialize (GutState * state);


// void ArrayConstructor (GutState * state);
// void ArrayGet (GutState * state);

// void GutArrayInit (void)
// {
//     GutObject array = {
//         { "Array", GutArray },
//         [
//             { "constructor", ArrayConstructor },
//             { "get",         ArrayGet         },
//             { "set",         ArraySet         },
//             { "exists",      ArrayExists      },
//             { NULL,          NULL             },
//         ]
//     };

//     GutCoreBuiltIn(array);
// }


#endif
