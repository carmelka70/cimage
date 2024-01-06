#include "reader.h"
#include "vars.h"

#define MAX_ITERATIONS 10

#define read4byteint(buffer) ((uint32_t)((*buffer << 24) | (*(buffer+1) << 16) | (*(buffer+2) << 8) | *(buffer+3)))

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

int
get_chunk(uint8_t *buffer ,chunk *c ,int skip_anc){
	uint32_t length = read4byteint(buffer);//gets the chunks length in big endiann

	if(skip_anc && ((int)(buffer[4]) >= 97 && (int)(buffer[4]) <= 122)){
		return length;
	}
	c->length = length;

	strncpy(c->type ,buffer + 4 ,4);//copys type from buffer
	c->type[4] = '\0';//adds \0 to string


	c->data = malloc(c->length);//allocates space for data based on length
	if(!c->data){//check if allocation was successfull
		printf("Failed to allocate space for data\n");
		exit(1);
	}
	memcpy(c->data ,buffer + 8 ,c->length);//copys data from buffer
	
	c->crc = read4byteint(buffer + (8 + c->length));//gets the chunks crc in big endiann
	return 0;
}


int
read_to_chunk_arr(uint8_t *buffer ,chunk **chunks ,int skip_anc){
	*chunks = NULL;//this will store the chunks

	uint8_t *bi = buffer + 8;//buffer index for the loop
	int index = 0;//store the current index spot

	while(index < MAX_ITERATIONS){
		*chunks = realloc(*chunks ,sizeof(chunk) * (index + 1));//adds a chunk at the end of chunks
		if(!*chunks){//check for errors at reallocation
			printf("Chunks failed to reallocate at index %d\n" ,index);
			free(*chunks);
			exit(1);
		}

		uint32_t status = get_chunk(bi ,*chunks + index ,skip_anc);//get chunk from buffer index to chunks at index index
		if (status){//if skip_anc is used and the chunk is anc increase buffer index and continue
			bi += 12 + status;
			continue;
		}
		if(!strncmp((*chunks)[index].type ,"IEND" ,5)){//checks for last chunk
			break;
		}

		bi += (12 + (*chunks)[index].length);//buffer index is being readjusted
		index++;//next iteration
	}
	return index;
}

void
print_data(chunk c){
	//prints chunk c data
	for(int i = 0; i < c.length; i++){
		printf("%d " ,c.data[i]);
	}
	printf("\n");
}

void
get_chunks_data(chunk *chunks ,int chunkslen){
	for(int i = 0; i < chunkslen; i++){
		char* type = chunks[i].type;
		if (!strncmp(type ,"IHDR" ,5)) get_IHDR(chunks[i].data);
		else if (!strncmp(type ,"PLTE" ,5)) get_PLTE(chunks[i].data); 
		else if (!strncmp(type ,"IDAT" ,5)) get_IDAT(chunks[i].data);
		else if (!strncmp(type ,"tRNS" ,5)) get_tRNS(chunks[i].data);
		else if (!strncmp(type ,"gAMA" ,5)) get_gAMA(chunks[i].data); 
		else if (!strncmp(type ,"cHRM" ,5)) get_cHRM(chunks[i].data);
		else if (!strncmp(type ,"sRGB" ,5)) get_sRGB(chunks[i].data);
		else if (!strncmp(type ,"iCCP" ,5)) get_iCCP(chunks[i].data);
		else if (!strncmp(type ,"tEXt" ,5)) get_tEXt(chunks[i].data);
		else if (!strncmp(type ,"zTXt" ,5)) get_zTXt(chunks[i].data);
		else if (!strncmp(type ,"iTXt" ,5)) get_iTXt(chunks[i].data);
		else if (!strncmp(type ,"bKGD" ,5)) get_bKGD(chunks[i].data);
		else if (!strncmp(type ,"pHYs" ,5)) get_pHYs(chunks[i].data);
		else if (!strncmp(type ,"sBIT" ,5)) get_sBIT(chunks[i].data);
		else if (!strncmp(type ,"hIST" ,5)) get_hIST(chunks[i].data);
		else if (!strncmp(type ,"tIME" ,5)) get_tIME(chunks[i].data);
		else if (!strncmp(type ,"IEND" ,5)) return; 
		else{
			printf("Failed to read chunk %d with type %s\n" ,i ,type);
			exit(1);
		}

	}
	
}
/*reading chunks into vars.h*/
void get_IHDR(uint8_t *data){
	uint32_t IHDR_width = read4byteint(data);
	uint32_t IHDR_height = read4byteint(data + 4);

	uint8_t IHDR_bit_depth = data[5];
	uint8_t IHDR_color_type = data[5];
	uint8_t IHDR_compression_method = data[5];
	uint8_t IHDR_filter_method = data[5];
	uint8_t IHDR_interlace_method = data[5];

};
void get_PLTE(uint8_t *data){};
void get_IDAT(uint8_t *data){
	uint8_t *IDAT_data = data;
};
void get_tRNS(uint8_t *data){};
void get_gAMA(uint8_t *data){};
void get_cHRM(uint8_t *data){};
void get_sRGB(uint8_t *data){};
void get_iCCP(uint8_t *data){};
void get_tEXt(uint8_t *data){};
void get_zTXt(uint8_t *data){};
void get_iTXt(uint8_t *data){};
void get_bKGD(uint8_t *data){};
void get_pHYs(uint8_t *data){};
void get_sBIT(uint8_t *data){};
void get_hIST(uint8_t *data){};
void get_tIME(uint8_t *data){};

