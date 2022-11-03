#include "odot.h"

extern FILE *fp;


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
