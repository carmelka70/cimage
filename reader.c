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
void get_chunk(uint8_t *buffer ,chunk *c);


int
main(){

	uint8_t *buffer;

	read_file("C:\\Users\\carmil\\workspace\\cimage\\image.png" ,&buffer);	

	for(int i = 0; i < 16; i++){
		printf("%d\n" ,buffer[i]);
	}

	chunk newcnk;
	get_chunk(buffer + 8 ,&newcnk);

	printf("\ntype:%s\nlength:%d" ,newcnk.type ,newcnk.length);

	free(newcnk.data);
    return 0;
}


void read_file(const char *filename ,uint8_t **buffer){
	FILE *fp;
	fp = fopen(filename ,"rb");

	if(!fp){ 
		printf("ERR: failed to read file %s\n" ,filename);
		exit(0);
	}

	fseek(fp ,0 ,SEEK_END);
	size_t filesize = ftell(fp);

	fseek(fp ,0 ,SEEK_SET);

	printf("the size is %d\n" ,filesize);

	*buffer = malloc(filesize);

	if (!*buffer){
		printf("Failed to allocate space for buffer\n");
		fclose(fp);
		exit(1);
	}

	fread(*buffer ,1 ,filesize ,fp);

	fclose(fp);
}

void get_chunk(uint8_t *buffer ,chunk *c){
	c->length = (uint32_t)((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3]);

	strncpy(c->type ,buffer + 4 ,4);

	c->type[5] = '\0';

	c->data = malloc(c->length);
	
	if(!c->data){
		printf("Failed to allocate space for data\n");
		exit(1);
	}

	memcpy(c->data ,buffer + 8 ,c->length);
	
	c->crc = (uint32_t)buffer[8 + c->length];	
}
