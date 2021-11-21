#ifndef BITCODE_H
#define BITCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum _Registers {
    R_0  = 0,   // Null value
    R_lv = 1,   // Deposit and stack value
    R_pc = 2,   // Program value
    R_rt = 3,   // Resulting value
    R_o0 = 4,   // Operation valu
    R_o1 = 5,   // Operation value
    R_h0 = 6,  
    R_v0 = 7,
    R_a0 = 8,
    R_a1 = 9,
    R_a2 = 10,
    R_a3 = 11,
    R_t0 = 12,
    R_t1 = 13,
    R_t2 = 14,
    R_t3 = 15,
    R_t4 = 16,
    R_t5 = 17,
    R_t6 = 18,
    R_t7 = 19,
    R_s0 = 20,
    R_s1 = 21,
    R_s2 = 22,
    R_s3 = 23,
    R_s4 = 24,
    R_s5 = 25,
    R_s6 = 26,
    R_s7 = 27,  
    R_gp = 28,
    R_sp = 29,
    R_fp = 30,
    R_ra = 31,
    R_count
};

uint32_t reg[R_count];

enum _Operations {
    OP_DEPOSIT  = 0b00,

    OP_LOAD     = 0b100,
    OP_UNLD     = 0b101,

    OP_JMP      = 0b01, 

    OP_SKP      = 0b11000100,

    OP_ADD      = 0b11000000,
    OP_SUB      = 0b11000001,

    OP_PUSH     = 0b11000010,
    OP_POP      = 0b11000011,

    OP_LBL      = 0b1110,

    OP_EXT      = 0b11111111,
    OP_PRT      = 0b11111110,
};

// enum _Type { };
#endif