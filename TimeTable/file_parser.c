#include "file_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_BUFFER
#define MAX_TEACHERS 1000

// TODO - Provision to ignore lines starting with #
// TODO - Error check and handling that first string read from file is integer

int parse_file(char* file_name, char*** array, int* size){
	FILE *fp;
	char temp_word_buffer[100];
	int temp_word_buffer_length;
	int temp_size = 0;
	int retval;

	if (file_name == NULL) {
		printf("Error in parseFile(...), fileName NULL\n");
		return 0;
	}

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error in parseFile(...), cannot open file %s\n", file_name);
		return 0;
	}

	if(EOF == fscanf(fp, "%d", size)) {
        printf("Error in parseFile(...), empty file %s\n", file_name);
    	return 0;
	}
    *array = (char **)malloc((*size) * sizeof(char *));

	if (*array == NULL) {
		printf("Error in parse_file(...), insufficient memory for array\n");
		fclose(fp);
		return 0;
	}

	while (EOF != fscanf(fp, "%s", temp_word_buffer)) {
	    temp_word_buffer_length = strlen(temp_word_buffer);
		char *word = (char *)malloc(temp_word_buffer_length * sizeof(char));
		if (word == NULL) {
			printf("Error in parse_file(...), insufficient memory for word\n");
			delete_array((void **)(*array), temp_size);
			fclose(fp);
			return 0;
		}
		strcpy(word, temp_word_buffer);
		(*array)[temp_size++] = word;
	}

	if (*size != temp_size) {
		printf("Error in parse_file(...), size %d is not equal to value %d from %s\n",
                temp_size, *size, file_name);
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}

void delete_array(void** array, int size){
	while(size > 0){
		free(array[size - 1]);
		size--;
	}
	free(array);
}

void print_char_array(char** array, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%s\n", array[i]);
    }
    printf("Total elements = %d\t size = %d\n", i, size);
}
