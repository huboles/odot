#include "odot.h"

/* global variables */ 
int showdone = 0,
    showall  = 0,
    exists   = 0;

u_long hash;

char    *group,
        *newgroup,
        *task,
        *action;

int main(int argc, char *argv[]){
    /* show help if no arguments unless its just showing tasks */
    if (argc == 2 && strcmp(argv[1],"show") != 0) help();

    sqlite3 *db;
    int err = sqlite3_open(filepath(),&db);
    sqlcmd(db,BUILDTABLE,'c');

    /* show all tasks if called alone */
    if (argc == 1) {
        showall = 1;
        show(db);
        sqlite3_close(db);
        exit(0);
    }

    group = calloc(MAXLINE,sizeof(char));
    task = calloc(MAXLINE,sizeof(char));
    action = calloc(MAXLINE,sizeof(char));
    newgroup = calloc(MAXLINE,sizeof(char));
    
    parseopt(argc,argv);
    hash = genhash();

    operate(db);

    sqlite3_close(db);
    return 0;
}

void parseopt(int n, char **args){
    char c;
    while ((c = getopt(n,args,"g:G:adh")) != -1){
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
                strcpy(group,optarg);
                break;
            case 'G':
                strcpy(newgroup,optarg);
                break;
            case '?':
                error(4);
                break;
        }
    }

    /* get subcommand */
    strcpy(action,args[optind]);

    /* rest of arguments become task */
    for (int j = optind + 1; j < n; j++){
            strcat(task,args[j]);
            strcat(task,(j != n-1) ? " " : "");
    }
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
        case 4:
            fprintf(stderr,"Unknown Command\n");
            help();
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
