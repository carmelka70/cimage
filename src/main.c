#include <stdio.h>
#include "reader.h"

int
main(int argc ,char *argv[]){
	if(argc > 2){
		printf("ERROR: too many arguments\n");
		return 1;
	}
	if(argc == 1){
		printf("ERROR: please specify the image path\n");
		return 1;
	}
	
	uint8_t *buffer;
	read_file(argv[1] ,&buffer);


	chunk *chunks;
	int chunkslen = read_to_chunk_arr(buffer ,&chunks);

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
