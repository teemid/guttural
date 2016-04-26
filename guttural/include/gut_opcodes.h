#ifndef GUTTURAL_OPCODE_H
#define GUTTURAL_OPCODE_H


enum GutturalOpCode
{
    OP_JUMP,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_CALL
} GutOpCode;


extern char const * const guttural_opcodes[];


#endif
