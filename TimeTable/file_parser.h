#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "time_table.h"
#include "global.h"

extern char **teacher_array;
extern char **sub_array;
extern char **days_array;
extern char **std_array;

extern int parse_file(char* file_name, char*** array, int *size);
extern void delete_array(void** array, int size);
extern void print_char_array(char** array, int size);
extern void print_tl_array(teacher_lec_t* tl_array, int num_teacher_lec);
extern int parse_periods_file(char* file_name, int *num_periods);
extern int parse_lec_file0(char* file_name, teacher_lec_t** tl_array,
                          int *num_teach_lec);
extern int parse_lec_file1(char* file_name, teacher_lec_t** tl_array,
                          int *num_teach_lec);
extern void delete_tl_array(teacher_lec_t **tl_array, int t_size, int l_size);
extern int parse_constraints(char* file_name);

#endif // FILE_PARSER_H
