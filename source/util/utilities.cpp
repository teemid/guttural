#include <iostream>

#include "guttural.hpp"
#include "guttural/lexer.hpp"
#include "guttural/util/file_reader.hpp"
#include "guttural/util/string_reader.hpp"


namespace Guttural
{
    void InterpretFile (char * filename)
    {
        auto reader = FileReader(filename);
        auto lexer = Lexer(&reader);

        while (lexer.Next() != Kind::EndOfFile)
        {
            std::cout << "Hello\n";
        }
    }

    void InterpretString (char * input)
    {
        auto reader = StringReader(input);
        auto lexer = Lexer(&reader);

        while (lexer.Next() != Kind::EndOfFile)
        {
            std::cout << "Hello\n";
        }
    }
}

