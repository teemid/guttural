#ifndef GUTTURAL_H
#define GUTTURAL_H


namespace Guttural
{
    // Opaque struct holding the execution state.
    struct Fiber;

    // Utility functions.
    void InterpretFile (char * filename);
    void InterpretString (char * input);
}

#endif
