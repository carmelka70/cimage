#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//chunk struct
// length: 4 byte int in big-endiann
// type: 4 byte string of the chunks type
// data: length byte the data of the chunk
// crc: 4 byte crc information
typedef struct{
	uint32_t length;
	char type[5];
	uint8_t *data;
	uint32_t crc;
}chunk;

void read_file(const char *filename ,uint8_t **buffer);//reads filename into buffer
int get_chunk(uint8_t *buffer ,chunk *c ,int skip_anc);//gets chunk at buffer (bi) into c. when skip_anc is used returns either 0 for importent chunk or length for anc chunk
int read_to_chunk_arr(uint8_t *buffer ,chunk **chunks ,int skip_anc);//reads buffer into chunks array. use skip_anc to skip anc chunks
void print_data(chunk c);//prints chunk c data

void get_chunks_data(chunk *chunks ,int chunkslen);


/*reading chunks into vars.h*/
void get_IHDR(uint8_t *data);
void get_PLTE(uint8_t *data);
void get_IDAT(uint8_t *data);
void get_tRNS(uint8_t *data);
void get_gAMA(uint8_t *data);
void get_cHRM(uint8_t *data);
void get_sRGB(uint8_t *data);
void get_iCCP(uint8_t *data);
void get_tEXt(uint8_t *data);
void get_zTXt(uint8_t *data);
void get_iTXt(uint8_t *data);
void get_bKGD(uint8_t *data);
void get_pHYs(uint8_t *data);
void get_sBIT(uint8_t *data);
void get_hIST(uint8_t *data);
void get_tIME(uint8_t *data);

#endif
