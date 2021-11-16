#ifndef BAE_UTIL_H
#define BAE_UTIL_H

#include <stdio.h>
#include <stdlib.h>

#include "bytebuffer.h"

char* read_ascii_file(char* path);
void write_binary_file(const char* path, Bytebuffer* bbuffer);

#endif