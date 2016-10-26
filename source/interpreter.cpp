#include "guttural/interpreter.hpp"
#include "guttural/fiber.hpp"


namespace Guttural
{
    Interpreter::Interpreter (Fiber * fiber) : fiber(fiber) { }
}
