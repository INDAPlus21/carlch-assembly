#ifndef BAE_PARSER_H
#define BAE_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

#include "../include/token.h"

enum _ParserStatus {
    PARSER_SUCCESS,
    PARSER_SYNTAX_ERROR
};
typedef enum _ParserStatus ParserStatus;

ParserStatus parser_start(TokenList* list, char* source);
uint32_t parser_get_number(char* buf);
TokenInst parser_get_inst(char* buf);
TokenRegister parser_get_reg(const char* buf);

#endif