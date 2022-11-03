#include "odot.h"

extern int urgency;
extern FILE *fp;


struct task maketask(char *task, char *group){
    struct task tmp;

    tmp.task = task;
    tmp.date = 0;
    tmp.group = group;

    return tmp;
}

void puttask(struct task n){
    fprintf(fp, "%s\t%i\t%s\n",n.task,n.date,n.group);
}

struct task gettask(void){
    struct task tmp;
    
    fscanf(fp,"%s\t%i\t%s\n",tmp.task,&tmp.date,tmp.group);

    return tmp;
}
