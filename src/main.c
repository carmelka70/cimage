#include <stdio.h>
#include "reader.h"

int
main(int argc ,char *argv[]){

	if (argc != 3){
		printf("not the correct amount of arguments\n");
		return 1;
	}
	
	uint8_t *buffer;
	read_file(argv[1] ,&buffer);

	char* arg2 = argv[2];
	int skip_anc;
	if (!strcmp(arg2 ,"true")){
		skip_anc = 0;
	}
	else if (!strcmp(arg2 ,"false")){
		skip_anc = 1;
	}
	else{
		printf("Second argument is invalid. please choose either true or false\n");
		return 1;
	};


	chunk *chunks;
	int chunkslen = read_to_chunk_arr(buffer ,&chunks ,skip_anc);

	free(buffer);

	for(int i = 0; i < chunkslen; i++){
		printf("type:%s\nlength:%d\n\n" ,chunks[i].type ,chunks[i].length);
		if (!strcmp(chunks[i].data ,"IDAT")){
			print_data(chunks[i]);
		}
	}

	for(int i = 0; i < chunkslen; i++){
		free(chunks[i].data);
	}

	free(chunks);

	return 0;

}
