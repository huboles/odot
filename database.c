#include "odot.h"

extern char *group,
            *task;


sqlite3 *accessdb(char *file){
    sqlite3 *db;

    int err = sqlite3_open(file, &db);
    if (err) sqlerror(db); 

    return db;
}

void sqlcmd(sqlite3 *db, char *cmd){
    int err = sqlite3_exec(db,cmd,NULL,NULL,NULL);
    if (err) sqlerror(db); 
    return;

}

void sqlprint(sqlite3 *db, char *cmd){
    int err = sqlite3_exec(db,cmd,printcallback,0,NULL);
    if (err) sqlerror(db); 
    return;

}

void sqlgroup(sqlite3 *db, char *cmd){
    int err = sqlite3_exec(db,cmd,groupcallback,0,NULL);
    if (err) sqlerror(db); 
    return;

}


void sqlerror(sqlite3 *db) {
    fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    error(1);
}

int printcallback(void *unused,int argc, char **argv, char **name){
    int i = 1;

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

int groupcallback(void *unused,int argc, char **argv, char **name){
    strcpy(group,argv[0]);
    return 0;
}
