#include "odot.h"

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};


int listcheck(struct task t){
    char *s = malloc(strlen(t.task) * sizeof(char));

    fp = fopen(TODOLIST, "r");
    if (fp == NULL)
        error('f');

    while (fgets(s, strlen(t.task), fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(t.task, s) == 0){
            free(s);
            return 1;
        }
    }
    free(s);
    return 0;
}


char *gettime(void){
    return NULL;
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
