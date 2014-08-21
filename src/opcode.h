#ifndef opcode_h
#define opcode_h

typedef enum {
    OP_IADD,
    OP_ISUB,
    OP_IMUL,
    OP_IDIV,
    OP_ILT,
    OP_IEQ,
    OP_BR,          // Branch
    OP_BRT,         // Branch if true
    OP_BRF,
    OP_ICONST,      // Push constant integer
    OP_CALL,
    OP_RETURN,
    OP_LOAD,
    OP_GLOAD,
    OP_STORE,
    OP_GSTORE,
    OP_PRINT,
    OP_POP,
    OP_HALT
} OpCode;

extern char const * opcode_names[];

#endif