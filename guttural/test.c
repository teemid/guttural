#include <stdio.h>
#include <string.h>

#include "guttural.h"
#include "gut_core.h"

int main (int argc, char ** argv)
{
    argc; argv;

    GutState * state = GutNewState();

    GutCoreInitialize (state);

    return 0;
}
