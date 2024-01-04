#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct{
	uint32_t length;
	char type[5];
	uint8_t *data;
	uint32_t crc;
}chunk;

void read_file(const char *filename ,uint8_t **buffer);
int get_chunk(uint8_t *buffer ,chunk *c ,int skip_anc);
int read_to_chunk_arr(uint8_t *buffer ,chunk **chunks ,int skip_anc);
void print_data(chunk c);

#endif
