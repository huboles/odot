#include "odot.h"

/* global variables */ 
int showdone = 0,
    showall  = 0;
char    *group,
        *task;

int main(int argc, char *argv[]){
    sqlite3 *db;
    db = accessdb("odot.db");
    buildtables(db);

    /* print all todo tasks if called alone */ 
    if (argc == 1) {
        print(db);
        return 0;
    }

    group = malloc(MAXLINE * sizeof(char));
    task = malloc(MAXLINE * sizeof(char));
    
    char *action = malloc(100*sizeof(char));
    
    strcpy(action,argv[1]);
    parseopt(argc,argv);
    struct task t = maketask(task,group);

    free(task);
    free(group);


    operate(action,t,db);

    sqlite3_close(db);
    return 0;
}

void parseopt(int n, char **args){
    char c;
    while ((c = getopt(n,args,"g:ad")) != -1){
        switch (c) {
            case 'a':
                showall = 1;
                break;
            case 'd':
                showdone = 1;
                break;
            case 'g':
                strcpy(group,optarg);
                break;
            case '?':
                printf("Unknown Option: %c\n", optopt);
        }
    }

    if (strcmp(group, "") == 0) strcpy(group,"all");

    for (; optind < n; optind++){
        if (optind > 1) {
            strcat(task,args[optind]);
            strcat(task,(optind != n -1) ? " " : "");
        }  
    }
}

struct task maketask(char *task, char *group){
    struct task tmp;

    tmp.task = malloc(strlen(task)*sizeof(char));
    strcpy(tmp.task,task);

    tmp.group = malloc(strlen(group)*sizeof(char));
    strcpy(tmp.group,group);

    return tmp;
}

void operate(char *action, struct task t, sqlite3 *db){
    if (strcmp(action,"new") == 0){
        addtask(db, t);
    } else if (strcmp(action,"done") == 0){
        donetask(db, t);
    } else if (strcmp(action,"remove") == 0){
        removetask(db,t);
    } else if (strcmp(action,"show") != 0) {
        printf("Unknown subcommand: %s\n",action);
    }
    if (showall == 1) {
        if (showdone == 1) {
            printdone(db);
        } else {
            print(db);
        }
    } else {
        if (showdone == 1) {
            printgroupdone(db,t); 
        } else {
            printgroup(db,t);
        }
    }
}
