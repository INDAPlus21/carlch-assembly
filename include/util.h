#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opcodes.h"
#include "bytebuffer.h"

uint8_t memory[UINT8_MAX];

char* read_ascii_file(char* path);

uint8_t* read_binary_file(char* path);
void write_binary_file(char* path, Bytebuffer* bbuffer);

uint8_t read8(uint8_t* buffer, int index);
uint32_t read32(uint8_t* buffer, uint32_t index);

#endif