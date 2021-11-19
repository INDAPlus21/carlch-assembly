#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <stdlib.h>
#include <stdint.h>

typedef struct _Bytebuffer Bytebuffer;
struct _Bytebuffer {
    uint8_t* buffer;
    int ptr;
    int size;
};

Bytebuffer* byte_buffer_create(int size);
void byte_buffer_write(Bytebuffer* bbuffer, uint8_t data);
void byte_buffer_destroy(Bytebuffer* bbuffer);

#endif