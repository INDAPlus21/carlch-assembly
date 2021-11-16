#include "../include/parser.h"

ParserStatus parser_start(TokenList* list, char* source) {
    char lex[256];
    int lexi = 0;
    int i = 0;
    int line = 1;

    while(1) {
        // memset(lex, 0, 256);

        while(source[i] != ' ' && source[i] != '\n' && source[i] != '\0') {
            lex[lexi++] = source[i++];
        }
        lex[lexi] = '\0';

        // TODO Managae tabs and empty lines

        if(lex[0] == '\0')
            break;

        Token token;

        // Get number
        if(lex[0] == '#') {
            int num = parser_get_number(lex);
            token_create(&token, NUMBER, num, line);
            token_list_add(list, token);
        }

        else if(lex[0] == '%') {
            int reg = parser_get_reg(lex);
            if(reg >= 0) {
                token_create(&token, REGISTER, reg, line);
                token_list_add(list, token);
            } else {
                printf("Syntax error at %d : '%s'\n", line, lex);
                return PARSER_SYNTAX_ERROR;
            }
        }

        // Get instruction
        else {
            int inst = parser_get_inst(lex);
            if(inst >= 0) {
                token_create(&token, INST, inst, line);
                token_list_add(list, token);
            }
            else {
                printf("Syntax error at line %d : '%s'\n", line, lex);
                return PARSER_SYNTAX_ERROR;
            }
        }

        // Get new line
        if(source[i] == '\n') {
            line++;
        }
        // End of file
        else if(source[i] == '\0') {
            break;
        }

        // Reset lex
        lexi = 0;
        i++;
    }
    return PARSER_SUCCESS;
}

uint32_t parser_get_number(char* buf) {
    long num = atoi(&buf[1]);
    return(num <= UINT32_MAX) ? num : 0;
}

TokenInst parser_get_inst(char* buf) {
    if(strcmp(buf, "MOV") == 0)
        return MOV;
    if(strcmp(buf, "PUSH") == 0)
        return PUSH;
    if(strcmp(buf, "ADD") == 0)
        return ADD;
    if(strcmp(buf, "STOP") == 0)
        return STOP;
    return (TokenInst)-1;
}

TokenRegister parser_get_reg(const char* buf) {
    if(strcmp(buf, "%eax") == 0)
        return EAX;
    return (TokenRegister)-1;
}