#ifndef BEA_COMPILER_H
#define BEA_COMPILER_H

#include <stdio.h>

#include "bytecode.h"
#include "token.h"
#include "bytebuffer.h"

enum _CompilerStatus {
    COMPILER_SUCCESS,
    COMPILER_ERROR,
};
typedef enum _CompilerStatus CompilerStatus;

struct _Compiler {
    CompilerStatus status;
    TokenList* tokens;
    Bytebuffer* bytecode;
};
typedef struct _Compiler Compiler;

void compiler_start(Compiler* c);

#endif