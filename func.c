#include "odot.h"

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};


int listcheck(struct task t){
    char *s = malloc(t.length* sizeof(char));

    fp = fopen(TODOLIST, "r");
    if (fp == NULL)
        error('f');

    while (fgets(s, t.length, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(t.task, s) == 0){
            free(s);
            return 1;
        }
    }
    free(s);
    return 0;
}

int geturgency(int n){
    if(n > 0 && n <= 10){
        if (n > 7)
            return RED;
        else if (n > 3)
            return YELLOW;
        else
            return GREEN;
    } else {
        error('r');
    }
}

char *gettime(void){
    struct tm *s;
    time_t *t ;
    char *c = malloc(16*sizeof(char));

    *t = time(NULL);
    if (t == ((t) - 1)){
        error('t');
    }
    
    s = localtime(t);

    strftime(c, 16, "%y-%m-%d %H:%M", s);

    if (c == NULL){
        error('t');
    }

    return c;
}

int linecount(FILE *fp){
    int i = 0;
    char c;
    while ((c = fgetc(fp)) != EOF){
        if (c == '\n')
            i++;
    }
    rewind(fp);
    return i;
}
