#include "odot.h"


extern FILE *fp;

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

void add(struct task t, FILE *fp){
    char *c = malloc(strlen(t.task)*sizeof(char));
    FILE *fc = fopen("/tmp/odot", "w");
    int i = 0;
    
    while (fgets(c,strlen(t.task),fp) != NULL){
        switch (listcheck(t,fp)){
            case 3:
                dialogue("Already on todo list", t.task, CYAN);
                break;
            case 1:
                dialogue("Already on list in a different group", gettask(fp).group, YELLOW);
                /* confirm(); */
                break;
            default:
                if (i == 0 && strcmp(c,t.task) > 0){
                    puttask(t,fc);
                    ++i;
                }
        }
        puttask(gettask(fp), fc);
    }

    free(c);
    fclose(fp);
    fclose(fc);
    remove(TODOLIST);
    rename("/tmp/odot", TODOLIST);
    return; 
}


void rem(FILE *fp){
    char *s = malloc(MAXLINE * sizeof(char));
    FILE *fc = fopen("/tmp/odot", "w");

    while (fgets(s, MAXLINE, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(note, s) != 0){
            fputs(strcat(s,"\n"),fc);
        }
    }

    fclose(fp);
    fclose(fc);

    remove (TODOLIST);
    rename("/tmp/odot", TODOLIST);

    free(s);
}

void show(FILE *fp){
    char *c = malloc(sizeof(char));

    while (fgets(c, 1, fp) != NULL )
        formattask(gettask(fp));
    free(c);
}

