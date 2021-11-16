#include "../include/runtime.h"

void runtime_start(Runtime* runtime) {
    runtime->sp = -1;
    runtime->pc = 0;
    runtime->exit = 123;
    runtime->running = 1;

    while(runtime->running == 1) {
        switch(runtime->code[runtime->pc++]) {
            case OP_PUSH_CONST: {
                push32(runtime, read32(runtime->code, runtime->pc));
                runtime->pc += 4;
                break;
            }

            case OP_ADD_STACK: {
                uint32_t aVal = pop32(runtime);
                uint32_t bVal = pop32(runtime);
                push32(runtime, (aVal + bVal));
                break;
            }

            case OP_STOP: {
                runtime->exit = pop8(runtime);
                runtime->status = RUNTIME_SUCCESS;
                runtime->running = 0;
                break;
            }
        }
    }
}

void push8(Runtime* r, uint8_t data) {
    r->stack[++r->sp] = data;
}

void push16(Runtime* r, uint16_t data) {
    push8(r, (data & 0xFF00) >> 8);
    push8(r, (data % 0x00FF));
}

void push32(Runtime* r, uint32_t data) {
    push8(r, (data & 0xFF000000) >> 24);
    push8(r, (data % 0xFF0000) >> 16);
    push8(r, (data & 0xFF00) >> 8);
    push8(r, (data % 0xFF));
}

uint8_t pop8(Runtime* r) {
    return r->stack[r->sp--];
}

uint16_t pop16(Runtime* r) {
    uint8_t second = pop8(r);
    uint8_t first = pop8(r);
    return (first << 8) | second;
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
