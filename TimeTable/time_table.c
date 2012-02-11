#include "time_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_time_table(int num_teachers, int num_days, int num_periods){
    int i = 0, j = 0, k = 0;

    lecture_t*** time_table = (lecture_t***)malloc(sizeof(lecture_t**) * num_teachers);
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
                strcpy(time_table[i][j][k].sub, "\0");
                strcpy(time_table[i][j][k].std, "\0");
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

int allocate(int teacher, int day, int period) {
    /*
    // Here I do not know how to define lastTeacher, etc.
    // They need to be global variables, defined when file input is read
    // Can we use static for this
    // I FORGOT C :|
    if(teacher > lastTeacher) {
        teacher = firstTeacher;
        period++;
    }
    if(period > lastPeriod) {
        period = firstPeriod;
        day++:
    }
    if(day > lastDay)
        return true;
    */
    //continue...
}
