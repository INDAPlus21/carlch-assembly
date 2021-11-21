#include "../include/compiler.h"

void compiler_start(Compiler* c) {
    c->bytecode = byte_buffer_create(1);

    for(int i = 0; i < c->tokens->ptr; i++) {
        Token* tok = token_list_get(c->tokens, i);

        if(tok->type == INST) {
            switch(tok->data) {
                case DEPOSIT: {
                    if(token_list_get(c->tokens, i + 1)->type == VALUE) {
                        deposit(c, i);
                        i++;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }
                
                case LOAD: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER) {
                        uint8_t instData = ((OP_LOAD << 5)) | token_list_get(c->tokens, i + 1)->data;
                        byte_buffer_write(c->bytecode, instData);
                        i++;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case UNLD: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER) {
                        uint8_t instData = ((OP_UNLD << 5)) | token_list_get(c->tokens, i + 1)->data;
                        byte_buffer_write(c->bytecode, instData);
                        i++;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }
                
                case JMP: {
                    if(token_list_get(c->tokens, i + 1)->type == VALUE) {
                        uint8_t instData = ((OP_JMP << 6)) | token_list_get(c->tokens, i + 1)->data;
                        byte_buffer_write(c->bytecode, instData);
                        i++;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case SKP: {
                    byte_buffer_write(c->bytecode, OP_SKP);
                    break;
                }
                
                case ADD: {
                    byte_buffer_write(c->bytecode, OP_ADD);
                    break;
                }

                case SUB: {
                    byte_buffer_write(c->bytecode, OP_SUB);
                    break;
                }
    
                case PUSH: {
                    byte_buffer_write(c->bytecode, OP_PUSH);
                    break;
                }

                case POP: {
                    byte_buffer_write(c->bytecode, OP_POP);
                    break;
                }

                case EXT: {
                    byte_buffer_write(c->bytecode, OP_EXT);
                    break;
                }

                case PRT: {
                    byte_buffer_write(c->bytecode, OP_PRT);
                    break;
                }
                case LBL: {
                    if(token_list_get(c->tokens, i + 1)->type == VALUE) {
                        uint8_t lblData = ((OP_LBL << 4)) | token_list_get(c->tokens, i + 1)->data;
                        byte_buffer_write(c->bytecode, lblData);
                        i++;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                // MACROS

                case M_MOVE: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == REGISTER) {
                        unld(c, i);
                        push(c);
                        unld(c, i + 1);
                        load(c, i);
                        pop(c);
                        i += 2;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_LOAD: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == VALUE) {
                        deposit(c, i + 1);
                        load(c, i);
                        i += 2;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_ADD: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == REGISTER && token_list_get(c->tokens, i + 3)->type == REGISTER) {
                        unld(c, i + 1);
                        byte_buffer_write(c->bytecode, 0b10000100);
                        unld(c, i + 2);
                        byte_buffer_write(c->bytecode, 0b10000101);
                        add(c);
                        byte_buffer_write(c->bytecode, 0b10100011);
                        load(c, i);
                        i += 3;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_ADDI: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == REGISTER && token_list_get(c->tokens, i + 3)->type == VALUE) {
                        unld(c, i + 1);
                        byte_buffer_write(c->bytecode, 0b10000100);
                        deposit(c, i + 2);
                        byte_buffer_write(c->bytecode, 0b10000101);
                        add(c);
                        byte_buffer_write(c->bytecode, 0b10100011);
                        load(c, i);
                        i += 3;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_SUB: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == REGISTER && token_list_get(c->tokens, i + 3)->type == REGISTER) {
                        unld(c, i + 1);
                        byte_buffer_write(c->bytecode, 0b10000100);
                        unld(c, i + 2);
                        byte_buffer_write(c->bytecode, 0b10000101);
                        sub(c);
                        byte_buffer_write(c->bytecode, 0b10100011);
                        load(c, i);
                        i += 3;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_SUBI: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == REGISTER && token_list_get(c->tokens, i + 3)->type == VALUE) {
                        unld(c, i + 1);
                        byte_buffer_write(c->bytecode, 0b10000100);
                        deposit(c, i + 2);
                        byte_buffer_write(c->bytecode, 0b10000101);
                        sub(c);
                        byte_buffer_write(c->bytecode, 0b10100011);
                        load(c, i);
                        i += 3;
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_PUSH: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER) {
                        unld(c, i);
                        push(c);
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_POP: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER) {
                        pop(c);
                        load(c, i);
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_LOOP: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER && token_list_get(c->tokens, i + 2)->type == REGISTER && token_list_get(c->tokens, i + 3)->type == VALUE) {
                        // move variable in R_a0, R_a1 to stack
                        byte_buffer_write(c->bytecode, 0b10101000); // move a0
                        push(c);                                    // push to stack
                        byte_buffer_write(c->bytecode, 0b10101001); // move a1
                        push(c);                                    // push to stack

                        unld(c, i);                                 // Fetch value from first input val
                        byte_buffer_write(c->bytecode, 0b10001000); // Load value into a0
                        unld(c, i + 1);                             // Fetch value from second input val
                        byte_buffer_write(c->bytecode, 0b10001001); // Load value into a1

                        byte_buffer_write(c->bytecode, 0b10100100); // Unload current val from o0 to lv
                        push(c);
                        byte_buffer_write(c->bytecode, 0b10100101); // Unload current val from o1 to lv
                        push(c);

                        byte_buffer_write(c->bytecode, 0b10101001); // unload value from a1
                        byte_buffer_write(c->bytecode, 0b10000100); // Load into register o0
                        byte_buffer_write(c->bytecode, 0b00000001); // Deposit 1 into lv register
                        byte_buffer_write(c->bytecode, 0b10000101); // Load into register o1 
                        sub(c);                                     // Subtract by one
                        byte_buffer_write(c->bytecode, 0b10100011); // Unload result
                        load(c, i + 1);                             // Load lv (result) into second register

                        pop(c);
                        byte_buffer_write(c->bytecode, 0b10000101);
                        pop(c);
                        byte_buffer_write(c->bytecode, 0b10000100);

                        skp(c);      
                        
                        jmp(c, i + 2);                               // Call skip operator

                        // move back variable to registers
                        pop(c);
                        byte_buffer_write(c->bytecode, 0b10001001);
                        pop(c);
                        byte_buffer_write(c->bytecode, 0b10001000);

                        i += 3;

                        // jmp(c, (i + 2));
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                case M_PRINT: {
                    if(token_list_get(c->tokens, i + 1)->type == REGISTER) {
                        push(c);
                        unld(c, i);
                        prt(c);
                        pop(c);
                    } else {
                        printf("[%d] : Invalid instruction!\n", tok->line);
                        c->status = COMPILER_ERROR;
                        return;
                    }
                    break;
                }

                default:
                    printf("[%d] : Syntax error!\n", tok->line);
                    c->status = COMPILER_ERROR;
                    return;
            }
        }
    }
    c->status = COMPILER_SUCCESS;
}