#include "todo.h"

#define TODOLIST "/home/huck/info/notes/todo"

extern char *note;

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

FILE *fp;

void add(void){
    fp = fopen(TODOLIST, "a");
    if (fp != NULL){
        fputs(strcat(note,"\n"),fp);
        fclose(fp);
    }
}

void rem(void){
    char *s = malloc(MAXLINE * sizeof(char));
    FILE *tmp = fopen("temp", "w");

    fp = fopen(TODOLIST, "r");


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
    char *c;

    c = (char *) malloc(MAXLINE * sizeof(int));

    fp = fopen(TODOLIST,"r");
    while (fgets(c, MAXLINE, fp) != NULL )
        printf("\t\t\033[1;35m*\033[0m %s", c);
    fclose(fp);
    free(c);
}

int listcheck(void){
    char *s;

    fp = fopen(TODOLIST, "r");
    s = (char *) malloc(MAXLINE * sizeof(char));

    while (fgets(s, MAXLINE, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(note, s) == 0){
            free(s);
            return 1;
        }
    }
    free(s);
    return 0;
}
