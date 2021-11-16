#include "../include/util.h"

char* read_ascii_file(char* path) {
    // Create file
    FILE* file = fopen(path, "r");
    if(!file) {
        printf("Unable to open file '%s'\n", path);
        return NULL;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Read file
    char* buf = (char*) malloc(sizeof(char) * (size + 1));
    if(!buf) {
        printf("Count not allocate memory for file!\n");
        return NULL;
    }
    fread(buf, 1, size, file);
    buf[size] = '\0';
    fclose(file);
    // Return file contents
    return buf;
}

void write_binary_file(const char* path, Bytebuffer* bbuffer) {
    FILE* file = fopen(path, "wb");
    if(!file) {
        printf("Count not write to file '%s'\n", path);
        return;
    }
    fwrite(bbuffer->buffer, 1, bbuffer->ptr, file);
    fclose(file);
}