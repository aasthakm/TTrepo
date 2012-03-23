#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include "time_table.h"
#include "global.h"

extern int counter1;
extern int num_teachers;
extern int num_sub;
extern int num_days;
extern int num_std;
extern int num_periods;
extern int num_teach_lecs;

extern char **teacher_array;
extern char **sub_array;
extern char **days_array;
extern char **std_array;

int main()
{
    char *teacher_file = "input_data/teachers.txt";
    char *sub_file = "input_data/subjects.txt";
    char *days_file = "input_data/days.txt";
    char *std_file = "input_data/standards.txt";
    char *periods_file = "input_data/periods.txt";
    char *lec_file = "input_data/lectures1.txt";
    char *constraint_file = "input_data/constraints.txt";

    teacher_array = NULL;
    sub_array = NULL;
    days_array = NULL;
    std_array = NULL;

    teacher_lec_t *tl_array;

    //int retval = 0;
    counter1 = 0;
    num_teachers = 0;
    num_sub = 0;
    num_days = 0;
    num_std = 0;
    num_periods = 0;
    num_teach_lecs = 0;

    if(!parse_file(teacher_file, &teacher_array, &num_teachers))
    {
        printf("Error in main(...), parse_file returned 0 while parsing %s\n", teacher_file);
		return 0;
    }

    if(!parse_file(std_file, &std_array, &num_std))
    {
        printf("Error in main(...), parse_file returned 0 while parsing %s\n", std_file);
		return 0;
    }

    if(!parse_file(days_file, &days_array, &num_days))
    {
        printf("Error in main(...), parse_file returned 0 while parsing %s\n", days_file);
		return 0;
    }

    if(!parse_file(sub_file, &sub_array, &num_sub))
    {
        printf("Error in main(...), parse_file returned 0 while parsing %s\n", sub_file);
		return 0;
    }

    if(!parse_periods_file(periods_file, &num_periods))
    {
        printf("Error in main(...), parse_file returned 0 while parsing %s\n", periods_file);
		return 0;
    }

    if(!parse_lec_file1(lec_file, &tl_array, &num_teach_lecs))
    {
        printf("Error in main(...), parse_file returned 0 while parsing %s\n", lec_file);
		return 0;
    }

    print_tl_array(tl_array, num_teach_lecs);

    if(!init_time_table(num_teachers, num_days, num_periods))
    {
        printf("Error in main(...), init_time_table returned 0\n");
		return 0;
    }

    if(!parse_constraints(constraint_file))
    {
        printf("Error in main(...), parse_constraints returned 0 while parsing %s\n", constraint_file);
		return 0;
    }

    printf("\nTotal values %d, %d, %d", num_teachers, num_periods, num_days);
    allocate(tl_array, 0, 0, 0);
    printf("\ncounter1 = %d", counter1);

    return 0;
}
