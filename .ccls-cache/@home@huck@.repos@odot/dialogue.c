#include "odot.h"

void error(int err){
    switch (err) {
        case '1':
            fprintf(stderr,"ERROR: COULD NOT ACCESS FILE: %s\n", TODOLIST);
        case '2':
            fprintf(stderr,"ERROR: COULD NOT GET CURRENT TIME\n");
        case '3':
            fprintf(stderr,"ERROR: ARGUMENT OUT OF RANGE\n");
    }
    exit(err);
}

void dialogue(char *m1, char *m2, int c){
    printf("\033[1;3%im%s\033[0m: %s\n", c, m1, m2);
    return;
}

void formattask(struct task t){
    printf("* %s\t%s\t%i", t.task, t.group, t.date);
}

