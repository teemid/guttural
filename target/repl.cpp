#include <iostream>
#include "guttural.hpp"


int main (int argc, char * argv[])
{
    if (argc < 1)
    {
        std::cout << "Expected a filename.\n";
    }

    Guttural::InterpretFile(argv[0]);

    return 0;
}
