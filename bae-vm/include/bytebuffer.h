#ifndef BAE_BYTEBUFFER_H
#define BAE_BYTEBUFFER_H

#include <stdlib.h>
#include <stdint.h>

struct _Bytebuffer {
    uint8_t* buffer;
    int ptr;
    int size;
};
typedef struct _Bytebuffer Bytebuffer;

Bytebuffer* byte_buffer_create(int size);
void byte_buffer_write_8(Bytebuffer* bbuffer, uint8_t data);
void byte_buffer_write_16(Bytebuffer* bbuffer, uint16_t data);
void byte_buffer_write_32(Bytebuffer* bbuffer, uint32_t data);
void byte_buffer_destroy(Bytebuffer* bbuffer);

#endif