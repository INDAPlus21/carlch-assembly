#include "../include/parser.h"

ParserStatus parser_start(TokenList* list, char* source) {
    char lex[255];
    int lexi = 0;
    int i = 0;
    int line = 1;

    while(1) {
        while(source[i] != ' ' && source[i] != '\n' && source[i] != '\0')
            lex[lexi++] = source[i++];
            
        lex[lexi] = '\0';

        if (lexi == 0 && (source[i] == '\n' || source[i] == '\t')) {
			i++;
			if (source[i] == '\n') line++;
			continue;
		}

        if(lex[0] == '\0')
            break;

        Token token;
        // Get number
        if(lex[0] == ':') {
            int val = parser_get_value(lex);
            token_create(&token, VALUE, val, line);
            token_list_add(list, token);
        }
        // Get register
        else if(lex[0] == '@') {
            int reg = parser_get_value(lex);
            token_create(&token, REGISTER, reg, line);
            token_list_add(list, token);
        }
        // Get instruction
        else {
            int inst = parser_get_inst(lex);
            if(inst >= 0) {
                token_create(&token, INST, inst, line);
                token_list_add(list, token);
            }
            // If none above throw error
            else { 
                printf("[%d] : Syntax error (invalid instruction)!\n", line);
                return PARSER_SYNTAX_ERROR;
            }
        }

        if(source[i] == '\n')
            line++;
        else if(source[i] == '\0') 
            break;

        lexi = 0;
        i++;
    }
    return PARSER_SUCCESS;
}

uint8_t parser_get_value(char* buffer) {
    long val = atoi(&buffer[1]);
    return(val <= UINT8_MAX) ? val : 0;
}

Instructions parser_get_inst(char* buffer) {
    switch(lexer(buffer)) {
        case DEPOSIT: 
            return DEPOSIT;
        case LOAD: 
            return LOAD;
        case UNLD:
            return UNLD;
        case POP:
            return POP;
        case PUSH:
            return PUSH;
        case ADD:
            return ADD;
        case SUB:
            return SUB;
        case JMP:  
            return JMP;
        case EXT:  
            return EXT;
        case SKP:
            return SKP;
        case PRT:
            return PRT;
        case LBL:
            return LBL;

        // MACROS
        case M_MOVE:
            return M_MOVE;
        case M_LOAD:
            return M_LOAD;
        case M_ADD:
            return M_ADD;
        case M_ADDI:
            return M_ADDI;
        case M_SUB:
            return M_SUB;
        case M_SUBI:
            return M_SUBI;
        case M_PUSH:
            return M_PUSH;
        case M_POP:
            return M_POP;
        case M_LOOP:
            return M_LOOP;
        case M_PRINT:
            return M_PRINT;

        default:
            return (Instructions)-1;
    }
}

Instructions lexer(char* s) {
    struct entry_s {
        char* key;
        Instructions inst;
    }
    inst_table[] = {
        {"DEPOSIT", DEPOSIT},
        {"LOAD", LOAD},
        {"UNLOAD", UNLD},
        {"PUSH", PUSH},
        {"POP", POP},
        {"ADD", ADD},
        {"SUB", SUB},
        {"JUMP", JMP},
        {"EXIT", EXT},
        {"SKIP", SKP},
        {"PRT", PRT},
        {"LABEL", LBL},

        // MACROS
        {"M_MOVE", M_MOVE},
        {"M_LOAD", M_LOAD},
        {"M_ADD", M_ADD},
        {"M_ADDI", M_ADDI},
        {"M_SUB", M_SUB},
        {"M_SUBI", M_SUBI},
        {"M_PUSH", M_PUSH},
        {"M_POP", M_POP},
        {"M_LOOP", M_LOOP},
        {"M_PRINT", M_PRINT},
        {NULL, NULL}
    };
    struct entry_s* p = inst_table;
    for(; p->key != NULL && strcmp(p->key, s) != 0; p++);
    return p->inst;
}