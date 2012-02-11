#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include "time_table.h"

int main()
{
    printf("Hello world!\n");

// TODO (@aastha) - try to implement these points if ur free

// Get user input from the *.txt files
// Just need to make respective calls here
// Make sure all the comments are removed from the file
// And we need to still write special functions for lectures.txt and periods.txt

    char *teacher_file = "input_data/teachers.txt";
    char *sub_file = "input_data/subjects.txt";
    char *days_file = "input_data/days.txt";
    char *std_file = "input_data/standards.txt";
    char **teacher_array = NULL;
    char **sub_array = NULL;
    char **days_array = NULL;
    char **std_array = NULL;

    int retval = 0;
    int num_teachers = 0, num_sub = 0, num_days = 0, num_std = 0;

    retval = parse_file(teacher_file, &teacher_array, &num_teachers);
    printf("ret_teacher = %d\n", retval);
    retval = parse_file(std_file, &std_array, &num_std);
    printf("ret_std = %d\n", retval);
    retval = parse_file(days_file, &days_array, &num_days);
    printf("ret_days = %d\n", retval);
    retval = parse_file(sub_file, &sub_array, &num_sub);
    printf("ret_sub = %d\n", retval);

// Init the timte table structure based on the input values
// Again just need to make a call, implementation is done

// Start allocation
// Lets first try to implement the algo without any kind of validation
// This will be just the backtracking algo then trying all cases
// We can try running it on small test cases
// Once above feature is worknig well, we can introduce validations

    return 0;
}
