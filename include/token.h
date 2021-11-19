#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef enum _Types Types;
enum _Types {
    INST,
    VALUE,
    REGISTER,
};

typedef enum _Instructions Instructions;
enum _Instructions {
    DEPOSIT,
    LOAD,
    UNLD,
    POP,
    ADD,
    JMP,
    SKP,
    PUSH,
    SUB,
    EXT,

    // MACROS
    M_MOVE,
    M_LOAD,
    M_ADD,
    M_PUSH,
    M_POP,
    M_LOOP,
};

typedef struct _Token Token;
struct _Token {
    int type;
    int data;
    int line;
};

void token_create(Token* tok, int type, int data, int line);
void token_destroy(Token* tok);

typedef struct _TokenList TokenList;
struct _TokenList {
    Token* data;
    int ptr;
    int size;
};

void token_list_create(TokenList* list, int size);
void token_list_add(TokenList* list, Token tok);
Token* token_list_get(TokenList* list, int index);
void token_list_destroy(TokenList* list);

#endif