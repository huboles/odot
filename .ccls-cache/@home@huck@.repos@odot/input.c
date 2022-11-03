#include "odot.h"

extern char *note, *o;
extern int urgency;

char *getnote(int n, char *arg[]){
    char *s = malloc(MAXLINE * sizeof(char));

    while(--n > 0){
        if ((*++arg)[0] != '-'){
            strcat(s, *arg);
            strcat(s, (n > 1) ? " " : "");
        }
    }
    return s;
}

void getopt(int n, char *arg[]){
    char *c;

    if (n == 1){
        o = "s";
        return;
    }
    
    while (--n > 0 && (*++arg)[0] == '-'){
        c = malloc(strlen(*arg) * sizeof(char));
        c = *arg;
        strcat(o,(strchr(c, 'd')) ? "d" : "n");

        if (strchr(c,'s') != NULL){
            strcat(o,"s");
        }

        free(c);
    }
}

struct task maketask(char *task, char *group){
    struct task tmp;

    tmp.task = task;
    tmp.date = 0;
    tmp.group = group;

    return tmp;
}


struct task gettask(void){
    struct task tmp;
    
    fscanf(fp,"%s\t%i\t%s\n",tmp.task,&tmp.date,tmp.group);

    return tmp;
}
