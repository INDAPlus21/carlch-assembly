#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/opcodes.h"
#include "../include/token.h"
#include "../include/util.h"
#include "../include/parser.h"
#include "../include/compiler.h"
#include "../include/bytebuffer.h"
#include "../include/runtime.h"


int main(int argc, char** argv) {
    // Check for expected amount of arguments
    if(argc < 3) {
        printf("Too few arguments!\n");
        return 1;
    }

    if(strcmp(argv[1], "run") == 0) {
        uint8_t* code = read_binary_file(argv[2]);
        Runtime r;
        r.code = code;
        runtime_start(&r);

        if(r.status == RUNTIME_ERROR)
            return 1;

        printf("Program succesfully terminated.\n");
        return 0;
    }

    if(strcmp(argv[1], "compile") == 0) {
        char* source = read_ascii_file(argv[2]);
        TokenList tokens;
        token_list_create(&tokens, 1);
        ParserStatus pstat = parser_start(&tokens, source);
        if(pstat != PARSER_SUCCESS)
            return 1;

        Compiler c;
        c.tokens = &tokens;
        compiler_start(&c);
        if(c.status != COMPILER_SUCCESS)
            return 1;

        write_binary_file("a.bout", c.bytecode);

        byte_buffer_destroy(c.bytecode);
        token_list_destroy(&tokens);
        free(source);

        return 0;
    }

    return 1;
}