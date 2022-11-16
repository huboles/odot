#include "odot.h"

struct task getnote(int n, char *arg[], char *group){
    char *s = malloc(MAXLINE * sizeof(char));
    struct task tmp;
    
    if (n == 1)
            printf("\nreturn from note\n");
        return tmp;


    while(n-- > 0){ 
            printf("\n%i-nloop\n",n);
        if (*arg[0] != '-'){
            strcat(s, *arg);
            strcat(s, (n > 1) ? " " : "");
        } else if (strcmp(*arg,"-g") == 0){
            strcpy(group, *arg);
        }
    }
    strcpy(tmp.task, s);
    strcpy(tmp.group, group);
    free(s);
    return tmp;
}

/* uses a 3 bit number to represent options
    1 - show list
    2 - add to list
    4 - remove from list
*/
short getopt(int n, char *arg[]){
    short options;
    
                printf("\nreturn1\n");
    /* show list if no arguments given */
    if (n == 1)
        return 1;
    
                printf("\ncheckopt\n");
    while (--n > 0 && (*++arg)[0] == '-'){
        /* if theres a d delete, otherwise add */
        options += strchr(*arg, 's') ? 1 : 0;
        options += strchr(*arg, 'n') ? 2 : 0;
        options += strchr(*arg, 'd') ? 4 : 0;
    }
                printf("%i", options);
    if ((options - 5) > 0)
        error(2);
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

void puttask(struct task t, FILE *fp){
    fprintf(fp,"%s\t%s\t%i\n",t.task,t.group,t.date);
}
