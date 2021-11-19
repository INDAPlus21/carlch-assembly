#include "../include/compiler.h"

void deposit(Compiler* c, int i) {
    uint8_t instData = ((OP_DEPOSIT << 6)) | token_list_get(c->tokens, i + 1)->data;
    byte_buffer_write(c->bytecode, instData);
}

void load(Compiler* c, int i) {
    uint8_t instData = ((OP_LOAD << 5)) | token_list_get(c->tokens, i + 1)->data;
    byte_buffer_write(c->bytecode, instData);
}

void unld(Compiler* c, int i) {
    uint8_t instData = ((OP_UNLD << 5)) | token_list_get(c->tokens, i + 1)->data;                    
    byte_buffer_write(c->bytecode, instData);
}

void jmp(Compiler* c, int i) {
    uint8_t instData = ((OP_JMP << 6)) | token_list_get(c->tokens, i + 1)->data;
    byte_buffer_write(c->bytecode, instData);
}

void skp(Compiler* c) {
    byte_buffer_write(c->bytecode, OP_SKP);
}

void add(Compiler* c) {
    byte_buffer_write(c->bytecode, OP_ADD);
}

void sub(Compiler* c) {
    byte_buffer_write(c->bytecode, OP_SUB);
}

void push(Compiler* c) {
    byte_buffer_write(c->bytecode, OP_PUSH);
}

void pop(Compiler* c) {
    byte_buffer_write(c->bytecode, OP_POP);
}

void ext(Compiler* c) {
    byte_buffer_write(c->bytecode, OP_EXT);
}