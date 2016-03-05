#ifndef opcode_h
#define opcode_h

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_LT,
    OP_EQ,
    OP_CALL,
    OP_RETURN,
    OP_LOAD,
    OP_GLOAD,
    OP_STORE,
    OP_GSTORE,
    OP_PRINT,
    OP_POP,
    OP_HALT,
    OP_MAX_OPCODE
} OpCode;

extern char const * opcode_names[];

#endif
