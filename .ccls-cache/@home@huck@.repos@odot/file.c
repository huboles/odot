#include "odot.h"


extern char *note;
extern FILE *fp;

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};


void add(struct task t, int size){
    int l,m,h,i,len;
    FILE *fcopy;
    char *s;
    h = len = linecount();
    m = h / 2;
    l = 0;

    while (!(h == m && m == l)){
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
        fseek(fp, m, SEEK_SET);
    }

    fseek(fp, 0, SEEK_SET);
    fcopy = fopen("/tmp/fcopy", "w");

    for (i = 0; i < len;){
        if (i == m){
            fprintf(fp, "%s\t%i\t%s\n",t.task,t.date,t.group);
        } else {
            fgets(s, MAXLINE, fp);
            fputs(s, fcopy);
            i++;
        }
    }
    fclose(fp);
    fclose(fcopy);
    remove(TODOLIST);
    rename("/tmp/fcopy", TODOLIST);

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

