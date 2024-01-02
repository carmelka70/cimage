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
chunk get_chunk(uint8_t *buffer);


int
main(){
	uint8_t *buffer;

	read_file("C:\\Users\\carmil\\workspace\\cimage\\image.png" ,&buffer);	

	buffer = buffer + 8;

	chunk *chunks = NULL;

	int iteration = 0;

	while(iteration < 10){
		chunks = realloc(chunks ,sizeof(chunk) * (iteration + 1));
		if(!chunks){
			printf("Chunks failed to reallocate at iteration %d\n" ,iteration);
			free(chunks);
			return 1;
		}

		chunks[iteration] = get_chunk(buffer);

		if(!strcmp(chunks[iteration].type ,"IEND")){
			break;
		}

		buffer += (12 + chunks[iteration].length);
		iteration++;
	}

	for(int i = 0; i < iteration; i++){
		printf("type:%s\nlength:%d\n\n" ,chunks[i].type ,chunks[i].length);
	}

	for(int i = 0; i < iteration; i++){
		free(chunks[i].data);
	}

	free(chunks);


	free(buffer);
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

	printf("the size is: %d\n\n" ,filesize);

	*buffer = malloc(filesize);

	if (!*buffer){
		printf("Failed to allocate space for buffer\n");
		fclose(fp);
		exit(1);
	}

	fread(*buffer ,1 ,filesize ,fp);

	fclose(fp);
}

chunk
get_chunk(uint8_t *buffer){
	chunk c;
	c.length = (uint32_t)((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3]);

	strncpy(c.type ,buffer + 4 ,4);

	c.type[4] = '\0';

	c.data = malloc(c.length);
	
	if(!c.data){
		printf("Failed to allocate space for data\n");
		exit(1);
	}

	memcpy(c.data ,buffer + 8 ,c.length);
	
	c.crc = (uint32_t)buffer[8 + c.length];

	return c;	
}
