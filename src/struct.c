#include "odot.h"

extern OPTIONS options;

TASK buildtask(void){
    TASK tmp = malloc(sizeof(struct task));
    
    tmp->hash = 0;
    tmp->note = NULL;
    tmp->group = NULL;
    tmp->done = 0;
    tmp->in_db = 0;
    tmp->date = time(NULL);

    return tmp;
}

void freetask(TASK todo){
    if (todo->note)
        free(todo->note);
    if (todo->group)
        free(todo->group);

    free(todo);
    return;
}

void printtask(TASK todo){
    if (options & COLOR) {
        printf("\t\033[32m[\033[0m%s\033[32m]\033[0m - ",(todo->done == 1 ? "\033[31mX\033[0m" : " "));
    } else {
        printf("\t[%s] - ", (todo->done == 1 ? "X" : " "));
    }
    printf("%s",todo->note);
    if (options & DATE){
        printf("\t%s\n",ctime(&todo->date));
    } else {
        printf("\n");
    }
}

void filltask(TASK todo, char **sql){
    /* sql is return-array [hash, note, group, done, in_db, date] */
    todo->hash = strtol(sql[0],NULL,10); 

    todo->note = calloc((strlen(sql[1])+1),sizeof(char));
    strncpy(todo->note,sql[1],strlen(sql[1]));

    todo->group = calloc((strlen(sql[2])+1),sizeof(char));
    strncpy(todo->group,sql[2],strlen(sql[2]));

    todo->done = strtol(sql[3],NULL,10);
    todo->in_db = 1;

    long t = strtol(sql[4],NULL,10);
    todo->date = time(&t);
    
    return;
}
