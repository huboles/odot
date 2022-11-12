#include "odot.h"

extern char *note, *group;
extern int urgency;

char *getnote(int n, char *arg[]){
    char *s = malloc(MAXLINE * sizeof(char));

/* adds word to note if it doesn't start with - */
    while(--n > 0 && (*++arg)[0] != '-'){
            strcat(s, *arg);
            strcat(s, (n > 1) ? " " : "");
    }
    return s;
}

/* uses a 3 bit number to represent options
    1 - show list
    2 - add to list
    4 - remove from list
*/
short getopt(int n, char *arg[]){
    char *c;
    short options;

    /* show list if no arguments given */
    if (n == 1)
        return 1;
    
    while (--n > 0 && (*++arg)[0] == '-'){
        c = malloc(strlen(*arg) * sizeof(char));
        c = *arg;

        options += strchr(c, 'd') ? 4 : 2;
        options += strchr(c, 's') ? 1 : 0;

        /* if theres a g then add the next argument as a group */
        if (strchr(c,'g') != NULL){
            group = *++arg;
        }

        free(c);
    }

    return options;
}


struct task maketask(char *task, char *group){
    struct task tmp;

    tmp.task = task;
    tmp.date = 0;
    /* add to all group if group isn't specified */
    tmp.group = (strcmp(group,"") == 0) ? "all" : group;

    return tmp;
}


struct task gettask(FILE *fp){
    struct task tmp;
     
    fscanf(fp,"%s\t%s\t%i\n",tmp.task,tmp.group,&tmp.date);

    return tmp;
}
