#include "../include/runtime.h"

void runtime_start(Runtime* r) {
    r->running = 1;
    reg[R_pc] = 0;
    reg[R_sp] = -1;
    reg[R_0] = 0;
    uint32_t labels[8];

    while(read8(r->code, reg[R_pc]) != '\0' && r->running) {
        uint8_t inst = r->code[reg[R_pc]];
        uint8_t subop = inst;
        switch(inst >> 6) {
            // Deposit operation
            case OP_DEPOSIT: {
                reg[R_lv] = (uint32_t)(read8(r->code, reg[R_pc]) & 0b00111111);
                break;
            }

            // :)
            case 0b10: {
                switch(subop >> 5) {
                    // Load operation
                    case OP_LOAD: {
                        uint32_t dest = (uint32_t)(read8(r->code, reg[R_pc]) & 0b00011111);
                        reg[dest] = reg[R_lv];
                        break;
                    }
                    
                    // Pop operation
                    case OP_UNLD: {
                        uint32_t dest = (uint32_t)(read8(r->code, reg[R_pc]) & 0b00011111);
                        reg[R_lv] = reg[dest];
                        break;
                    }
                }
                break;
            }

            // Jump operation
            case OP_JMP: {
                    uint32_t dest = (uint32_t)(read8(r->code, reg[R_pc]) & 0b00001111);
                    reg[R_pc] = labels[dest];
                    break;
                break;
            }
        
            // :))
            case 0b11: {
                if(subop >> 4 == OP_LBL) {
                    uint8_t lbl = (uint8_t)(read8(r->code, reg[R_pc]) & 0b00001111);
                    labels[lbl] = reg[R_pc];
                    break;
                }
                switch(subop) {
                    case OP_ADD: {
                        reg[R_rt] = reg[R_o0] + reg[R_o1];
                        break;
                    }
                    case OP_SUB: {
                        reg[R_rt]=(reg[R_o1] > reg[R_o0]) ? 0 : reg[R_o0] - reg[R_o1]; 
                        break;
                    }
                    case OP_PUSH: {
                        push32(r, reg[R_lv]);
                        break;
                    }
                    case OP_POP: {
                        reg[R_lv] = (reg[R_sp] > 3) ? 0 : pop32(r);
                        break;
                    } 
                    case OP_SKP: {
                        reg[R_pc] += (reg[R_a0] == reg[R_a1]) ? 1 : 0;
                        break;
                    }
                    case OP_EXT: {
                        r->running = 0;
                        r->status = RUNTIME_SUCCESS;
                        break;
                    }
                    case OP_PRT: {
                        printf("System >> %d\n", reg[R_lv]);
                        break;
                    }
                }
                break;
            }
            default: 
                printf("?\n");
        }
        reg[R_pc]++;
    }
}

void push8(Runtime* r, uint8_t data) {
    r->stack[++reg[R_sp]] = data;
}
void push32(Runtime* r, uint32_t data) {
    push8(r, (data & 0xFF000000) >> 24);
    push8(r, (data % 0xFF0000) >> 16);
    push8(r, (data & 0xFF00) >> 8);
    push8(r, (data % 0xFF));
}

uint8_t pop8(Runtime* r) {
    return r->stack[reg[R_sp]--];
}
uint32_t pop32(Runtime* r) {
    uint8_t fourth = pop8(r);
    uint8_t third = pop8(r);
    uint8_t second = pop8(r);
    uint8_t first = pop8(r);
    return (first << 24)
    | (second << 16)
    | (third << 8)
    | (fourth);
}
