#ifndef BAE_BYTECODE_H
#define BAE_BYTECODE_H

// Opcodes
enum _Bytecode {
    NOP = 0x00,
    REG_MOV = 0x03,
    REG_ADD = 0x04,
    OP_PUSH_CONST = 0x01,
    OP_ADD_STACK = 0x02,
    OP_STOP = 0xFF
};
typedef enum _Bytecode Bytecode;

enum _Register {
    R_NULL = 0x00,
    R_1,
    R_2,
    R_3,
    R_4
    R_5,
    R_6,
    R_7,
    R_PC,
    R_COND,
    R_COUNT
};
typedef enum _Register Regsiter;

#endif