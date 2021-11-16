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

uint8_t* read_binary_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if(!file) {
        printf("Could not open file '%s'\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t* buffer = (uint8_t*) malloc(sizeof(uint8_t) * size);
    fread(buffer, 1, size, file);
    fclose(file);

    return buffer;
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

uint16_t read16(uint8_t* buffer, uint32_t index) {
    return (buffer[index] << 8) | (buffer[index + 1]);
}

uint32_t read32(uint8_t* buffer, uint32_t index) {
    return (buffer[index] << 24) 
    | (buffer[index + 1] << 16) 
    | (buffer[index + 2] << 8) 
    | (buffer[index + 3]);
}