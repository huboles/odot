#include "odot.h"


extern char *note;
extern FILE *fp;

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};


void add(struct task t, int size){
    int l,m,h,i;

    h = linecount();
    m = h / 2;
    l = 0;

    while (h != m  && m != l){
        i = strcmp(t.task,gettask().task);

        if (i < 0) {
            h = m;
        } else if (i > 0) {
            l = m;
        } else { 
            dialogue("Task already on list",t.task, BLUE);
            return;
        }

        m = (h + l)/2;
    }

    puttask(t);
    return;
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

