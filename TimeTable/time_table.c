#include "time_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int counter1;
extern int num_teachers;
extern int num_sub;
extern int num_days;
extern int num_std;
extern int num_periods;
extern int num_teach_lecs;

lecture_t ***time_table = NULL;

int init_time_table(int num_teachers, int num_days, int num_periods){
    int i = 0, j = 0, k = 0;

    time_table = (lecture_t***)malloc(sizeof(lecture_t**) * num_teachers);
    if(time_table == NULL) {
        printf("Error in init_time_table(...), insufficient memory for tt\n");
        return 0;
    }

    for (i = 0; i < num_teachers; i++) {
        time_table[i] = (lecture_t**)malloc(sizeof(lecture_t*) * num_days);
        if(time_table[i] == NULL) {
            printf("Error in init_time_table(...),"
                   " insufficient memory for tt[teacher=%d]\n", i);
            delete_time_table_per_teacher(time_table, i);
            return 0;
        }
    }

    for(i = 0; i < num_teachers; i++) {
        for(j = 0; j < num_days; j++) {
            time_table[i][j] = (lecture_t*)malloc(sizeof(lecture_t) * num_periods);
            if (time_table[i][j] == NULL) {
                printf("Error in init_time_table(...),"
                       " insufficient memory for tt[teacher=%d][day=%d]\n", i, j);
                delete_day_time_table_per_teacher(time_table, num_teachers, j);
                return 0;
            }
        }
    }

    for(i = 0; i < num_teachers; i++) {
        for(j = 0; j < num_days; j++) {
            for(k = 0; k < num_periods; k++) {
                strcpy(time_table[i][j][k].std, "\0");
                strcpy(time_table[i][j][k].sub, "\0");
            }
        }
    }

    return 1;
}

void delete_time_table_per_teacher(lecture_t*** time_table, int num_teachers) {
    int i;
    for (i = 0; i < num_teachers; i++) {
        if(time_table[i] != NULL) {
            free(time_table[i]);
        }
    }
    if(time_table != NULL) {
        free(time_table);
    }
}

void delete_day_time_table_per_teacher(lecture_t*** lecture, int num_teachers, int num_days) {
    int i, j;
    for (i = 0; i < num_teachers; i++) {
        for (j = 0; j < num_days; j++) {
            if(lecture[i][j] != NULL) {
                free(lecture[i][j]);
            }
        }
    }
    for (i = 0; i < num_teachers; i++) {
        if(lecture[i] != NULL) {
            free(lecture[i]);
        }
    }
    if(lecture != NULL) {
        free(lecture);
    }
}

// TODO: try to calculate max values of each index, so that don't
// have to pass parameters. can internally call delete_2d_array itself.
void delete_time_table(lecture_t*** time_table, int num_teachers,
                       int num_days, int num_periods) {
    int i, j;
    for (i = 0; i < num_teachers; i++) {
        for (j = 0; j < num_days; j++) {
            if(time_table[i][j] != NULL) {
                free(time_table[i][j]);
            }
        }
    }
    for (i = 0; i < num_teachers; i++) {
        if(time_table[i] != NULL) {
            free(time_table[i]);
        }
    }
    if(time_table != NULL) {
        free(time_table);
    }
}

void print_time_table() {
    int i, j, k;

    printf("\n\nPrinting timetable, %d days, %d periods and %d teachers\n",
            num_days, num_periods, num_teachers);

    printf("\nTid\t");
    for(j = 0; j < num_days; j++) {
        for(k = 0; k < num_periods; k++) {
            printf("D%dP%d\t", j, k);
        }
    }

    for(i = 0; i < num_teachers; i++) {
        printf("\nT%d\t", i);
        for(j = 0; j < num_days; j++) {
            for(k = 0; k < num_periods; k++) {
                printf("%s%s\t", time_table[i][j][k].std, time_table[i][j][k].sub);
            }
        }
    }
}

int allocate(teacher_lec_t* tl_array, int teacher, int day, int period) {
    /*
    // Here I do not know how to define lastTeacher, etc.
    // They need to be global variables, defined when file input is read
    // Can we use static for this
    // I FORGOT C :|

    */
    //continue...

    //print_time_table
    int i, j, k;

    //scanf("%c",&tempchar);
    //printf(", %c", tempchar);

    if(teacher >= num_teachers) {
        teacher = 0;
        period++;
    }

    if(period >= num_periods) {
        period = 0;
        day++;
    }

    if(day >= num_days) {
        counter1++;
        print_time_table();
        return 1;
    }

    //printf("\n%d, %d, %d", teacher, period, day);
    //allocate(tl_array, teacher + 1, day, period);

    for(i = 0; i < tl_array[teacher].num_lectures; i++) {
        strcpy(time_table[teacher][day][period].std, tl_array[teacher].lectures[i].std);
        strcpy(time_table[teacher][day][period].sub, tl_array[teacher].lectures[i].sub);
        allocate(tl_array, teacher + 1, day, period);
    }


    return 1;
}
