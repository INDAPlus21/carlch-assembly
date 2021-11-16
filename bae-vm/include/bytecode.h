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

#endif