#include "odot.h"

/* global variables */ 
int showdone = 0,
    showall  = 0;

char    *group,
        *task,
        *action;

int main(int argc, char *argv[]){
    if (argc == 1) help();

    sqlite3 *db;
    db = accessdb(filepath());
    sqlcmd(db,BUILDTABLE);


    group = malloc(MAXLINE * sizeof(char));
    task = malloc(MAXLINE * sizeof(char));
    action = malloc(MAXLINE * sizeof(char));
    
    parseopt(argc,argv);

    operate(db);

    sqlite3_close(db);
    return 0;
}

void parseopt(int n, char **args){
    char c;
    while ((c = getopt(n,args,"g:adh")) != -1){
        switch (c) {
            case 'h':
                help();
                break;
            case 'a':
                showall = 1;
                break;
            case 'd':
                showdone = 1;
                break;
            case 'g':
                sprintf(group,"%s",optarg);
                break;
            case '?':
                printf("Unknown Option: %c\n", optopt);
        }
    }

    sprintf(group,"%s",(strcmp(group,"") == 0) ? "" : group);
    sprintf(action,"%s",args[optind]);

    for (int j = optind + 1; j < n; j++){
            strcat(task,args[j]);
            strcat(task,(j != n-1) ? " " : "");
    }
}

void operate(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    if (strcmp(action,"new") == 0){
        sprintf(cmd,"%s%s' ,'%s', 0);",INSERT,task,group);
        sqlcmd(db,cmd);
    } else if (strcmp(action,"done") == 0){
        sprintf(cmd,"%s%s';",DONE,task);
        sqlcmd(db,cmd);
        sprintf(cmd,"%s%s';", GETGROUP,task);
        sqlgroup(db,cmd);
        sprintf(cmd,"SELECT Done, Task FROM Tasks WHERE Task = '%s'",task);
        printf("\n");
        sqlprint(db,cmd);
    } else if (strcmp(action,"remove") == 0){
        sprintf(cmd,"%s%s';",DELETE,task);
        sqlcmd(db,cmd);
    } else if (strcmp(action,"show") != 0) {
        fprintf(stderr,"\033[33;1mUnknown subcommand\033[0m: %s\n",action);
    }
    printf("\n\t\033[35;1mTODO\033[0m: \033[36m%s\033[0m\n\n",group);
    if (showall == 1) {
        if (showdone == 1) {
            sqlprint(db,PRINTALL);
        } else {
            sqlprint(db,PRINT);
        }
    } else {
        if (showdone == 1) {
            sprintf(cmd,"%s%s' ORDER BY Done;",PRINTGROUPALL,group);
            sqlprint(db,cmd);
        } else if (strcmp(group,"\t") != 0) {
            sprintf(cmd,"%s%s';",PRINTGROUP,group);
            sqlprint(db,cmd);
        } else {
            sqlprint(db,PRINT);
        }
    }
}

char *filepath(void){
    char *dir = getenv("XDG_DATA_HOME");
    char *db = malloc(MAXLINE * sizeof(char));

    if (!dir) {
        dir = getenv("HOME");    
        if (!dir) error(3);
        strcat(dir,"/.local/share");
    }
    strcat(dir,"/odot");

    DIR *test = opendir(dir);

    if (test) {
        closedir(test);
    } else {
        int err = mkdir(dir, 0777);
        if (err) error(2);
    }

    sprintf(db,"%s/odot.db",dir);

    return db;
}

void error(int err){
    switch (err) {
        case 1:
            fprintf(stderr,"^^ SQL error ^^\n");
            break;
        case 2:
            fprintf(stderr,"Could not create odot directory\n\t$XDG_DATA_HOME/odot\n");
            break;
        case 3:
            fprintf(stderr,"Could not determine $HOME\n");
            break;
    }
    exit(err);
}

void help(){
    printf("Usage: odot [subcommand] (task)\n");
    printf("\tSubcommands:\n");
    printf("\tnew\tadd new task to database\n");
    printf("\tdone\tmark task as done in database\n");
    printf("\tshow\tshow tasks in database\n");
    printf("\tremove\tremove task from database\t\n");
    printf("\tOptions:\n");
    printf("\t-a\tshow all groups\n");
    printf("\t-d\talso show completed tasks\n");
    printf("\t-g\tset group for task\n");
    printf("\t-h\tshow this help\n");

    exit(0);
}
