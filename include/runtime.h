#ifndef RUNTIME_H
#define RUNTIME_H

#include "bytebuffer.h"
#include "opcodes.h"
#include "util.h"

#define STACK_SIZE 1024

typedef enum _RuntimeStatus RuntimeStatus;
enum _RuntimeStatus {
    RUNTIME_SUCCESS,
    RUNTIME_ERROR,
};

typedef struct _Runtime Runtime;
struct _Runtime {
    uint8_t* code;
    RuntimeStatus status;
    int running;
    uint8_t stack[1024];
};

void runtime_start(Runtime* r);

void push8(Runtime* r, uint8_t data);
void push32(Runtime* r, uint32_t data);

uint8_t pop8(Runtime* r);
uint32_t pop32(Runtime* r);

#endif