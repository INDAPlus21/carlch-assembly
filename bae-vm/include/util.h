#ifndef BAE_UTIL_H
#define BAE_UTIL_H

#include <stdio.h>
#include <stdlib.h>

#include "bytebuffer.h"

char* read_ascii_file(char* path);

uint8_t* read_binary_file(const char* path);
void write_binary_file(const char* path, Bytebuffer* bbuffer);

uint16_t read16(uint8_t* buffer, uint32_t index);
uint32_t read32(uint8_t* buffer, uint32_t index);

#endif