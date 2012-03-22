#ifndef TIME_TABLE_H
#define TIME_TABLE_H

#define MAX_LECS_PER_TEACHER 30

int counter1;
int num_teachers;
int num_sub;
int num_days;
int num_std;
int num_periods;
int num_teach_lecs;

typedef char subject_t;
typedef char standard_t;
typedef char teacher_t;

typedef struct lecture_s {
    standard_t std[5];
    subject_t sub[100];
} lecture_t;

typedef struct teacher_lec_s {
    teacher_t *teacher;
    int num_lectures;
    lecture_t lectures[MAX_LECS_PER_TEACHER];
} teacher_lec_t;

extern lecture_t ***time_table;

extern int init_time_table(int num_teachers, int num_days, int num_periods);
extern void delete_time_table_per_teacher(lecture_t*** lecture, int i_index);
extern void delete_day_time_table_per_teacher(lecture_t*** lecture,
                                               int i_index, int j_index);
extern void delete_time_table(lecture_t*** time_table, int num_teachers,
                              int num_days, int num_periods);
extern int allocate(teacher_lec_t* tl_array, int teacher, int day, int period);
extern void print_time_table();
#endif //TIME_TABLE_H
