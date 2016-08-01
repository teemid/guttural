#ifndef GUTTURAL_OPCODE_H
#define GUTTURAL_OPCODE_H


/*
 *  Instructions are 32 bit wide and in the format:
 *
 *  [OpCode 6 bit Result 8 bit Operand 9 bit Operand 9 bit]
 */

#define MaskA(instruction) (instruction & 0x03FC0000)
#define MaskB(instruction) (instruction & 0x0003FD00)
// #define MaskC(instruction) (instruction & 0x000001FF)

#define OpCode(instruction)   (instruction)>>26
#define OperandA(instruction) MaskA(instruction)>>18
#define OperandB(instruction) MaskB(instruction)>>9
#define OperandC(instruction) (instruction & 0x000001FF)

#define MakeInstruction(code, a, b, c) (code >> 28) | (a >> 18) | (b >> 9) | c


typedef enum GutturalOpCode
{
    OP_STORE,
    OP_LOAD,
    OP_GSTORE,
    OP_GLOAD,
    OP_JUMP,
    OP_JMP_EQ,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_CALL,
    OP_CALL_FOREIGN
} GutOpCode;



extern char const * const guttural_opcodes[];


#endif
