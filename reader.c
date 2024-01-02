#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define MAX_ITERATIONS 10

//PNG uses a chunk format structure of
//4-byte length
//4-byte type
//length-byte data
//4-byte crc
//the int values are stored in big-endiann
typedef struct{
	uint32_t length;
	char type[5]; //create 5 chars to include \0
	uint8_t *data;
	uint32_t crc;
}chunk;

void read_file(const char *filename ,uint8_t **buffer); //Reads filename into buffer. stored in bytes
chunk get_chunk(uint8_t *buffer);//gets the chunk at buffer


int
main(){
	uint8_t *buffer;

	read_file("C:\\Users\\carmil\\workspace\\cimage\\image.png" ,&buffer);	

	chunk *chunks = NULL;//this will store the chunks

	uint8_t *bi = buffer + 8;//buffer index for the loop
	int index = 0;//store the current index spot

	while(index < MAX_ITERATIONS){
		chunks = realloc(chunks ,sizeof(chunk) * (index + 1));//adds a chunk at the end of chunks
		if(!chunks){//check for errors at reallocation
			printf("Chunks failed to reallocate at index %d\n" ,index);
			free(chunks);
			return 1;
		}

		chunks[index] = get_chunk(bi);//get chunk from buffer index to chunks at index index

		if(!strcmp(chunks[index].type ,"IEND")){//checks for last chunk
			break;
		}

		bi += (12 + chunks[index].length);//buffer index is being readjusted
		index++;//next iteration
	}

	for(int i = 0; i <= index; i++){//print all chunks type and length
		printf("type:%s\nlength:%d\n\n" ,chunks[i].type ,chunks[i].length);
	}

	for(int i = 0; i <= index; i++){//free all of the chunks data
		free(chunks[i].data);
	}

	free(chunks);

	free(buffer);
    return 0;
}


void
read_file(const char *filename ,uint8_t **buffer){
	
	//reads the file
	FILE *fp;
	fp = fopen(filename ,"rb");

	if(!fp){ 
		printf("ERR: failed to read file %s\n" ,filename);
		exit(0);
	}

	//get filesize using ftell and fseek
	fseek(fp ,0 ,SEEK_END);
	size_t filesize = ftell(fp);

	fseek(fp ,0 ,SEEK_SET);

	//prints the size. may be romved
	printf("the size is: %d\n\n" ,filesize);

	//allocates memory for the buffer
	*buffer = malloc(filesize);

	//check if buffer allocated successfully
	if (!*buffer){
		printf("Failed to allocate space for buffer\n");
		fclose(fp);
		exit(1);
	}

	//read the filestream into the buffer
	fread(*buffer ,1 ,filesize ,fp);

	//close file
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
