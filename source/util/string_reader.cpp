#include "guttural/util/string_reader.hpp"


namespace Guttural
{
    StringReader::StringReader (char * input)
    {
        this->input = input;
        this->current = this->input;

        while (this->current != '\0')
        {
            this->current++;
        }

        this->end = this->current;
        this->current = this->input;
    }

    StringReader::StringReader (char * input, size_t length)
    {
        this->input = input;
        this->current = this->input;
        this->end = this->input + length;
    }

    StringReader::~StringReader (void)
    {

    }

    char * StringReader::Next (void)
    {
        static char c = 'a';

        return &c;
    }
}