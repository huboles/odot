#include "odot.h"


extern char *note;
extern FILE *fp;

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

void add(void){
    fp = fopen(TODOLIST, "a");
    if (fp == NULL)
        error('f');
    fputs(strcat(note,"\n"),fp);
    fclose(fp);
}

void rem(void){
    char *s = malloc(MAXLINE * sizeof(char));
    FILE *tmp = fopen("temp", "w");

    fp = fopen(TODOLIST, "r");
    if (fp == NULL)
        error('f');


    while (fgets(s, MAXLINE, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(note, s) != 0){
            fputs(strcat(s,"\n"),tmp);
        }
    }

    fclose(fp);
    fclose(tmp);

    remove (TODOLIST);
    rename("temp", TODOLIST);

    free(s);
}

void show(void){
    char *c = (char *) malloc(MAXLINE * sizeof(int));

    if (fp == NULL)
        error('f');

    while (fgets(c, MAXLINE, fp) != NULL )
        printf("\t\t\033[1;3%im*\033[0m %s",geturgency(urgency), c);
    fclose(fp);
    free(c);
}

