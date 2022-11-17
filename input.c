#include "odot.h"

struct task getnote(int n, char *arg[], char *group){
    char *note = malloc(MAXLINE * sizeof(char));
    struct task tmp;
    
    if (n == 1){
            printf("\t\treturn from note\n");
        return tmp;
    }


    while(--n > 0){ 
            printf("\t%i-nloop\n",n);
        if ((*++arg)[0] != '-'){
            strcat(note, *arg);
            strcat(note, " ");
        } else if (strcmp(*arg,"-g") == 0){
            strcpy(group, (*++arg));
            n--;
        }
    }
                printf("\t%s %s getnote\n",note,group);
    tmp = maketask(note,group);
    free(note);
    return tmp;
}

/* uses a 3 bit number to represent options
    1 - show list
    2 - add to list
    4 - remove from list
*/
short getopt(int n, char *arg[]){
    short options;
    
                printf("\treturn1\n");
    /* show list if no arguments given */
    if (n == 1)
        return 1;
    
                printf("\tcheckopt\n");
    while (--n > 0 && (*++arg)[0] == '-'){
        /* if theres a d delete, otherwise add */
        options += strchr(*arg, 's') ? 1 : 0;
        options += strchr(*arg, 'n') ? 2 : 0;
        options += strchr(*arg, 'd') ? 4 : 0;
    }
                printf("\t%i-optcode\n", options);
    if ((options - 5) > 0)
        error(2);
    return options;
}


struct task maketask(char *task, char *group){
            printf("\tmaketask\n");
    struct task tmp;
    
    tmp.task = malloc(strlen(task) * sizeof(char));
    tmp.group = malloc(strlen(group) * sizeof(char));

    strcpy(tmp.task,task);
    strcpy(tmp.group,(strcmp(tmp.group,"") == 0) ? "all" : group);

            printf("\t%s-task %s-group\n",tmp.task,tmp.group);

    return tmp;
}


struct task gettask(char *c){
            printf("\tgettask\n");
    struct task tmp;
     
    sscanf(c,"%s\t%s",tmp.task,tmp.group);

    return tmp;
}

void puttask(struct task t, FILE *fp){
            printf("\t%s %s puttask\n", t.task, t.group);
    fprintf(fp,"%s\t%s\n",t.task,t.group);
}
