#include "odot.h"

/* global variables */ 
int showdone = 0,
    showall  = 0,
    quiet    = 0,
    exists   = 0;

u_long hash;

char    *group,
        *newgroup,
        *task,
        action;

int main(int argc, char *argv[]){
    /* show help if just subcommand called, unless its just showing tasks */
    if (argc == 2 && strcmp(argv[1],"show") != 0) help();

    int err = 0;
    sqlite3 *db;
    err = sqlite3_open(filepath(),&db);
    if (err < 0) sqlerror(db);
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
    newgroup = calloc(MAXLINE,sizeof(char));
    
    parseopt(argc,argv);
    hash = genhash();

    /* checks if task already exists in db */
    dbcheck(db);

    switch (action){
        case 'n':
            newtask(db);
            break;
        case 'd':
            done(db);
            break;
        case 'u':
            update(db);
            break;
        case 'r':
            removetask(db);
            break;
        case 's':
            /* always gets shown unless quiet is set */
            break;
        case '?':
            error(CMDERR);
    }

    /* show db after action */
    if (quiet == 0){
        show(db);
    }

    sqlite3_close(db);
    return 0;
}

void parseopt(int n, char **args){
    char c;
    while ((c = getopt(n,args,"g:G:adhqV")) != -1){
        switch (c) {
            case 'h':
                help();
                break;
            case 'V':
                printf("v%s\n",VERSION);
                exit(0);
                break;
            case 'a':
                showall = 1;
                break;
            case 'd':
                showdone = 1;
                break;
            case 'q':
                quiet = 1;
                break;
            case 'g':
                strcpy(group,optarg);
                break;
            case 'G':
                strcpy(newgroup,optarg);
                break;
            case '?':
                error(FLAGERR);
                break;
        }
    }

    /* get subcommand char */
    action = args[optind][0];

    /* rest of arguments become task */
    for (int j = optind + 1; j < n; j++){
            strcat(task,args[j]);
            strcat(task,(j != n-1) ? " " : "");
    }
}

void error(int err){
    switch (err) {
        case SQLERR:
            fprintf(stderr,"^^ SQL error ^^\n");
            break;
        case DIRERR:
            fprintf(stderr,"Could not create odot directory\n\t$XDG_DATA_HOME/odot\n");
            break;
        case ENVERR:
            fprintf(stderr,"Could not determine $HOME\n");
            break;
        case FLAGERR:
            fprintf(stderr,"Unknown Flag\n");
            help();
            break;
        case CMDERR:
            fprintf(stderr,"Unknown Subcommand\n");
            help();
            break;
        case GRPERR:
            fprintf(stderr,"Specify new group with -G\n");
            break;
    }
    exit(err);
}

void help(){
    printf("Usage: odot [subcommand] (task)\n");
    printf("Subcommands:\n");
    printf("\tnew\tadd new task to database\n");
    printf("\tdone\tmark task as done in database\n");
    printf("\tupdate\tupdate task group, requires -G\n");
    printf("\tshow\tshow tasks in database\n");
    printf("\tremove\tremove task from database\t\n");
    printf("Option flags:\n");
    printf("\t-a\tshow all groups\n");
    printf("\t-d\talso show completed tasks\n");
    printf("\t-g\tset group for task\n");
    printf("\t-G\tnew group for update");
    printf("\t-q\tdon't show tasks\n");
    printf("\t-V\tversion information\n");
    printf("\t-h\tshow this help\n");


    exit(0);
}
