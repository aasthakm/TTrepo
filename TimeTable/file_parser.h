#ifndef FILE_PARSER_H
#define FILE_PARSER_H

extern int parse_file(char* file_name, char*** array, int *size);
extern void delete_array(void** array, int size);
extern void print_char_array(char** array, int size);

#endif // FILE_PARSER_H
