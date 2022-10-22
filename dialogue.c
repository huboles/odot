#include "odot.h"

void error(char type){
    switch (type) {
        case 'f':
            fprintf(stderr,"ERROR: COULD NOT ACCESS FILE: %s\n", TODOLIST);
            exit(1);
        case 't':
            fprintf(stderr,"ERROR: COULD NOT GET CURRENT TIME\n");
            exit(2);
        case 'r':
            fprintf(stderr,"ERROR: ARGUMENT OUT OF RANGE\n");
            exit(3);
    }
}

void dialogue(char *m1, char *m2, int c){
    printf("\033[1;3%im%s\033[0m: %s\n", c, m1, m2);
    return;
}
