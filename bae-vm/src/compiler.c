#include "../include/compiler.h"

void compiler_start(Compiler* c) {
    c->bytecode = byte_buffer_create(1);

    for(int i = 0; i < c->tokens->ptr; i++) {
        Token* t = token_list_get(c->tokens, i);

        if(t->type == INST) {
            switch (t->data) {
                case PUSH:
                    if(token_list_get(c->tokens, i + 1)->type == NUMBER) {
                        byte_buffer_write_8(c->bytecode, OP_PUSH_CONST);
                        byte_buffer_write_32(c->bytecode, token_list_get(c->tokens, i + 1)->data);
                        i++;
                    } else {
                        printf("Invalid PUSH inst\n");
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;

                case ADD: 
                    byte_buffer_write_8(c->bytecode, OP_ADD_STACK);
                    break;
                
                case STOP:
                    byte_buffer_write_8(c->bytecode, OP_STOP);
                    break;
                
                default:
                    printf("Invalid operation\n");
                    c->status = COMPILER_ERROR;
                    return;
            }
        }
    }

    c->status = COMPILER_SUCCESS;
}