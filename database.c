#include "odot.h"

extern char *group,
            *newgroup,
            *task;

extern u_long hash;
extern int exists;

void sqlcmd(sqlite3 *db, char *cmd, char action){
    int err = 0;
    switch (action) {
        case 'q':
            err = sqlite3_exec(db,cmd,NULL,NULL,NULL);
            break;
        case 'p':
            err = sqlite3_exec(db,cmd,printcallback,0,NULL);
            break;
        case 't':
            err = sqlite3_exec(db,cmd,taskcallback,0,NULL);
            break;
        case 'c':
            err = sqlite3_exec(db,cmd,checkcallback,0,NULL);
            break;
    }
    if (err < 0) sqlerror(db); 
    return;
}

void sqlerror(sqlite3 *db) {
    fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    error(1);
}

int printcallback(void *unused,int argc, char **argv, char **name){
    int i = 1;
        
        /* print group if it changes */
    if (argv[2]){
        char *g = malloc(strlen(argv[1])*sizeof(char));
        sprintf(g,"%s",argv[1]);
        if (strcmp(g,group) != 0) {
            sprintf(group,"%s",argv[1]);
            printf("\n\t\033[34m%s\033[0m\n",argv[1]);
        }
        i = 2;
    }

    printf("\t\033[32m[\033[0m%s\033[32m]\033[0m - ", (strcmp(argv[0],"1") == 0) ? "\033[31;1mX\033[0m" : " ");
    printf("%s\n",argv[i]);
    return 0;
}

int taskcallback(void *unused,int argc, char **argv, char **name){
    sprintf(task,"%s",argv[0]);
    sprintf(group,"%s",argv[1]);
    hash = strtoul(argv[2],NULL,10);
    return 0;
}

int checkcallback(void *unused,int argc, char **argv, char **name){
    if (exists == 1) return 0;
    if (hash == strtoul(argv[2],NULL,10)) {
        exists = 1;
    } else if (strcmp(task,argv[0]) == 0) {
        checksame(task,argv[1]);
    }
    return 0;
}
