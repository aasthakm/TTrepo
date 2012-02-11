#ifndef TIME_TABLE_H
#define TIME_TABLE_H

typedef char subject_t;
typedef char standard_t;
typedef char teacher_t;

typedef struct lecture_s {
    char std[5];
    char sub[100];
} lecture_t;

extern lecture_t ***time_table;

extern int init_time_table(int num_teachers, int num_days, int num_periods);
extern void delete_time_table_per_teacher(lecture_t*** lecture, int i_index);
extern void delete_day_time_table_per_teacher(lecture_t*** lecture, int i_index, int j_index);
extern void delete_time_table(lecture_t*** time_table, int num_teachers,
                              int num_days, int num_periods);
<<<<<<< HEAD
extern int allocate(int teacher, int day, int period);
=======
extern void allocate(int teacher, int day, int period);

>>>>>>> f1f5bd29ea66336178ce1d30c5c67b4df813a1ec
#endif //TIME_TABLE_H
