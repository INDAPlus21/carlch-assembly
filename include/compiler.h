#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>

#include "opcodes.h"
#include "token.h"
#include "bytebuffer.h"
#include "util.h"

typedef enum _CompilerStatus CompilerStatus;
enum _CompilerStatus {
    COMPILER_SUCCESS,
    COMPILER_ERROR,
};

typedef struct _Compiler Compiler;
struct _Compiler {
    CompilerStatus status;
    TokenList* tokens;
    Bytebuffer* bytecode;
};

void compiler_start(Compiler* c);
Instructions lexer(char* s);

void deposit(Compiler* c, int i);
void load(Compiler* c, int i);
void unld(Compiler* c, int i);
void jmp(Compiler* c, int i);
void skp(Compiler* c);
void add(Compiler* c);
void sub(Compiler* c);
void push(Compiler* c);
void pop(Compiler* c);
void ext(Compiler* c);
void prt(Compiler* c);
void lbl(Compiler* c, int i);

#endif