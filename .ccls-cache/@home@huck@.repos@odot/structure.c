#include "odot.h"

extern int urgency;
extern FILE *fp;


struct task maketask(int n, char **arg){
    struct task temp;

    temp.task = getnote(n,arg);
    temp.length = strlen(temp.task);
    temp.date = gettime();
    temp.due = 0;
    temp.urgency = urgency;

    return temp;
}

void puttask(struct task n){
    fprintf(fp, "%i\t%s\t%s\t%s\t%i\n",n.length,n.task,n.date,n.due,n.urgency);
}

struct task gettask(void){
    struct task tmp;
    
    fscanf(fp,"%i\t%s\t%s\t%s\t%i\n",&tmp.length,tmp.task,tmp.date,tmp.due,&tmp.urgency);

    return tmp;
}
