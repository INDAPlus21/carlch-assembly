#ifndef BAE_TOKEN_H
#define BAE_TOKEN_H

#include <stdlib.h>

enum _TokenType {
    INST,
    NUMBER
};

enum _TokenInst {
    PUSH,
    ADD,
    STOP
};
typedef enum _TokenInst TokenInst;

struct _Token {
    int type;
    int data;
    int line;
};
typedef struct _Token Token;

Token* token_create(int type, int data, int line);
void token_destory(Token* tok);

struct _TokenList {
    Token** data;
    int ptr;
    int size;
};
typedef struct _TokenList TokenList;

void token_list_create(TokenList* list, int size);
void token_list_add(TokenList* list, Token* tok);
Token* token_list_get(TokenList* list, int index);
void token_list_destory(TokenList* list);

#endif