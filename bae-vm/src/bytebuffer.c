#include "../include/bytebuffer.h"

Bytebuffer* byte_buffer_create(int size) {
    Bytebuffer* bbuffer = (Bytebuffer*) malloc(sizeof(Bytebuffer));
    bbuffer->buffer = (uint8_t*) malloc(sizeof(uint8_t) * size);
    bbuffer->ptr = 0;
    bbuffer->size = size;
    return bbuffer;
}

void byte_buffer_write_8(Bytebuffer* bbuffer, uint8_t data) {
    if(bbuffer->ptr >= bbuffer->size) {
        bbuffer->size *= 2;
        bbuffer->buffer = (uint8_t*) realloc(bbuffer->buffer, sizeof(uint8_t) * bbuffer->size);
    }
    bbuffer->buffer[bbuffer->ptr++] = data;
}

void byte_buffer_write_16(Bytebuffer* bbuffer, uint16_t data) {
    byte_buffer_write_8(bbuffer, (data & 0xFF00) >> 8);
    byte_buffer_write_8(bbuffer, (data & 0xFF));
}

void byte_buffer_write_32(Bytebuffer* bbuffer, uint32_t data) {
    byte_buffer_write_8(bbuffer, (data & 0xFF000000) >> 24);
    byte_buffer_write_8(bbuffer, (data & 0xFF0000) >> 16);
    byte_buffer_write_8(bbuffer, (data & 0xFF00) >> 8);
    byte_buffer_write_8(bbuffer, (data & 0xFF));
}

void byte_buffer_destroy(Bytebuffer* bbuffer) {
    free(bbuffer->buffer);
    free(bbuffer);
}