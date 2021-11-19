#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

#include "token.h"

typedef enum _ParserStatus ParserStatus;
enum _ParserStatus {
    PARSER_SUCCESS,
    PARSER_SYNTAX_ERROR,
};

ParserStatus parser_start(TokenList* list, char* source);
uint8_t parser_get_value(char* buffer);
Instructions parser_get_inst(char* buffer);
Instructions lexer(char* s);

#endif