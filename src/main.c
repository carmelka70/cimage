#include <stdio.h>
#include "reader.h"
#include "vars.h"

int
main(int argc ,char *argv[]){

	if (argc != 3){// check if argument count is right
		printf("not the correct amount of arguments\n");
		return 1;
	}
	
	uint8_t *buffer;
	read_file(argv[1] ,&buffer); //reads file into buffer

	//change skip_anc based on argv2
	//for argv2 = "true", the program will print only importent chunks
	//for argv2 = "false", the program will print all chunks
	char* arg2 = argv[2];
	int skip_anc;
	if (!strcmp(arg2 ,"true")){
		skip_anc = 1;
	}
	else if (!strcmp(arg2 ,"false")){
		skip_anc = 0;
	}
	else{
		printf("Second argument is invalid. please choose either true or false\n");
		return 1;
	};

	//get chunks array from buffer
	chunk *chunks;
	int chunkslen = read_to_chunk_arr(buffer ,&chunks ,skip_anc);
	free(buffer);

	//print chunks
	for(int i = 0; i < chunkslen; i++){
		printf("type:%s\nlength:%d\n\n" ,chunks[i].type ,chunks[i].length);
		if (!strcmp(chunks[i].data ,"IDAT")){
			print_data(chunks[i]);
		}
	}

	//free chunks data and array
	for(int i = 0; i < chunkslen; i++){
		free(chunks[i].data);
	}
	free(chunks);

	return 0;

}
