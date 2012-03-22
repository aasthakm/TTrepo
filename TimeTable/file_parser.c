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

	if (file_name == NULL) {
		printf("Error in parse_file(...), fileName NULL\n");
		return 0;
	}

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error in parse_file(...), cannot open file %s\n", file_name);
		return 0;
	}

	if(EOF == fscanf(fp, "%d", size)) {
        printf("Error in parse_file(...), empty file %s\n", file_name);
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

int parse_periods_file(char *file_name, int *num_periods) {
    FILE *fp;
    if (file_name == NULL) {
		printf("Error in parse_file(...), fileName NULL\n");
		return 0;
	}

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error in parse_file(...), cannot open file %s\n", file_name);
		return 0;
	}

	if(EOF == fscanf(fp, "%d", num_periods)) {
        printf("Error in parse_file(...), empty file %s\n", file_name);
    	return 0;
	}
	fclose(fp);
	return 1;
}

int parse_lec_file(char *file_name, teacher_lec_t **tl_array,
                   int *num_teach_lec) {
    FILE *fp;
    int i, j;
    char temp_word_buffer[100];
    int temp_num_lec, temp_word_buffer_length;
    teacher_lec_t *tla;

    if (file_name == NULL) {
		printf("Error in parse_lec_file(...), fileName NULL\n");
		return 0;
	}

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error in parse_lec_file(...), cannot open file %s\n", file_name);
		return 0;
	}

	if(EOF == fscanf(fp, "%d", num_teach_lec)) {
        printf("Error in parse_lec_file(...), empty file %s\n", file_name);
        fclose(fp);
    	return 0;
	}

	*tl_array = (teacher_lec_t*)malloc(sizeof(teacher_lec_t) * (*num_teach_lec));
	tla = *tl_array;
	if (!*tl_array) {
        printf("Error in parse_lec_file(...), insufficient memory for tl_array\n");
        fclose(fp);
        return 0;
	}

	for (i = 0; i < *num_teach_lec; i++) {
        if (EOF == fscanf(fp, "%s %d", temp_word_buffer, &temp_num_lec)) {
            printf("Error in parse_lec_file(...), iteration %d", i);
            delete_tl_array(tl_array, i, MAX_LECS_PER_TEACHER);
            fclose(fp);
            return 0;
        }
        temp_word_buffer_length = strlen(temp_word_buffer);
        // TODO: add assert (temp_word_buffer_length != 0)
        tla[i].teacher = (char*)malloc(temp_word_buffer_length * sizeof(char));
        if (!tla[i].teacher) {
            printf("Error in parse_lec_file(...), insufficient memory for tl_array.teacher\n");
            delete_tl_array(tl_array, i+1, MAX_LECS_PER_TEACHER);
            fclose(fp);
            return 0;
        }
        strcpy(tla[i].teacher, temp_word_buffer);
        for (j = 0; j < temp_num_lec; j++) {
            if (EOF == fscanf(fp, "%s %s", tla[i].lectures[j].std,
                              tla[i].lectures[j].sub)) {
                printf("Error...\n");
                delete_tl_array(tl_array, i+1, MAX_LECS_PER_TEACHER);
                fclose(fp);
                return 0;
            }
        }
        // TODO: assert (j == temp_num_lec)
        if (j == temp_num_lec) {
            tla[i].num_lectures = temp_num_lec;
        } else {
            printf("Error...\n");
            delete_tl_array(tl_array, i+1, MAX_LECS_PER_TEACHER);
        }
	}
	// TODO: assert (i == num_teach_lec)
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
}

void print_tl_array(teacher_lec_t* tl_array, int tl_array_size)
{
    int i, j;
    for(i = 0; i < tl_array_size; i++) {
        printf("%s >> ", tl_array[i].teacher);
        for(j = 0; j < tl_array[i].num_lectures; j++)
        {
            printf("%s %s, ", tl_array[i].lectures[j].std, tl_array[i].lectures[j].sub);
        }
        printf("\n");
    }
}

void delete_tl_array(teacher_lec_t **tl_array, int t_size, int l_size) {
    int i, j;
    teacher_lec_t *tla = *tl_array;
    for (i = 0; i < t_size; i++) {
        if (tl_array[i]) {
            if (tla[i].teacher) {
                free((void *)tla[i].teacher);
            }
            for (j = 0; j < l_size; j++) {
                if (tla[i].lectures[j].std) {
                    strcpy(tla[i].lectures[j].std, "\0");
                }
                if (tla[i].lectures[j].sub) {
                    strcpy(tla[i].lectures[j].sub, "\0");
                }
            }
            free((void *)tl_array[i]);
        }
    }
}
