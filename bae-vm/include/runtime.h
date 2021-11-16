#ifndef BAE_RUNTIME_H
#define BAE_RUNTIME_H

#include "bytebuffer.h"
#include "bytecode.h"
#include "util.h"

#define STACK_SIZE 1024

enum _RuntimeStatus {
    RUNTIME_SUCCESS,
    RUNTIME_ERROR,
};
typedef enum _RuntimeStatus RuntimeStatus;

typedef struct _Register Register;
struct _Register {};

struct _Runtime {
    uint8_t* code;
    RuntimeStatus status;
    uint8_t stack[STACK_SIZE];
    uint32_t sp;
    uint32_t pc;
    uint8_t exit;
    int running;            // 1 is true, 0 is false
};
typedef struct _Runtime Runtime;

void runtime_start(Runtime* runtime);

void push8(Runtime* r, uint8_t data);
void push16(Runtime* r, uint16_t data);
void push32(Runtime* r, uint32_t data);

uint8_t pop8(Runtime* r);
uint16_t pop16(Runtime* r);
uint32_t pop32(Runtime* r);

#endif