#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/util.h"
#include "../include/parser.h"
#include "../include/token.h"
#include "../include/compiler.h"

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Too few arguments!\n");
        return 1;
    }
    
    #ifdef DEBUG
        printf("DEBUG\n");
    #endif

    if(strcmp(argv[1], "compile") == 0) {
        char* source = read_ascii_file(argv[2]);
        TokenList tokens;
        token_list_create(&tokens, 1);
        ParserStatus pstat = parser_start(&tokens, source);
        if(pstat != PARSER_SUCCESS) {
            return 1;
        }

        Compiler comp;
        comp.tokens = &tokens;
        compiler_start(&comp);
        if(comp.status != COMPILER_SUCCESS)
            return 1;

        write_binary_file("a.bout", comp.bytecode);

        byte_buffer_destroy(comp.bytecode);

        // TODO Remove for debug
        for(int i = 0; i < tokens.ptr; i++) {
            Token* t = token_list_get(&tokens, i);
            printf("%d, %d, %d\n", t->type, t->data, t->line);
        }

        token_list_destory(&tokens);
        free(source);
    }

    return 0;
}