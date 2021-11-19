#include "../include/bytebuffer.h"

Bytebuffer* byte_buffer_create(int size) {
    Bytebuffer* bbuffer = (Bytebuffer*) malloc(sizeof(Bytebuffer));
    bbuffer->buffer = (uint8_t*) malloc(sizeof(uint8_t) * size);
    bbuffer->ptr = 0;
    bbuffer->size = size;
    return bbuffer;
}

void byte_buffer_write(Bytebuffer* bbuffer, uint8_t data) {
    bbuffer->buffer[bbuffer->ptr++] = data;
}

void byte_buffer_destroy(Bytebuffer* bbuffer) {
    free(bbuffer->buffer);
    free(bbuffer);
}