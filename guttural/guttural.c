#include <stdio.h>
#include <string.h>

#include "guttural.h"
#include "gut_core.h"


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("guttural expects a source file to read.");

        return 0;
    }

    GutState * state = GutNewState();

    GutCoreInitialize (state);

    GutDoFile(state, argv[1]);

    return 0;
}
