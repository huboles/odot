#include "odot.h"

extern int urgency;
extern FILE *fp;

struct task {
    int length;
    char *task;
    int date;
    int due;
    int urgency;
};

struct task maketask(int n, char **arg){
    struct task temp;

    temp.task = getnote(n,arg);
    temp.length = strlen(temp.task);
    temp.date = 0;
    temp.due = 0;
    temp.urgency = urgency;

    return temp;
}

void puttask(struct task n){
    fp = fopen(TODOLIST, "w");

    if (fp == NULL){
        error('f');
    }

    fprintf(fp, "%i\t%s\t%i\t%i\t%i\n",n.length,n.task,n.date,n.due,n.urgency);
    
}

struct task gettask(char *c){
    struct task tmp;
    
    sscanf(c,"%i\t%s\t%i\t%i\t%i\n",&tmp.length,tmp.task,&tmp.date,&tmp.due,&tmp.urgency);

    return tmp;
}
