#include "odot.h"

extern ACTION action;
extern OPTIONS options;

void parseopts(int n, char **args, TASK todo){
    char c;
    while ((c = getopt(n,args,"hVvg:aAdqcnrtsx")) != -1){
        switch (c) {
            /* info */
            case 'h':
                help();
                break;
            case 'V':
                printf("v%s\n",VERSION);
                exit(0);
                break;
            /* options */
            case 'a':
                options |= SHOWALL;
                break;
            case 'd':
                options |= SHOWDONE;
                break;
            case 'A':
                options |= (SHOWALL | SHOWDONE);
                break;
            case 'q':
                options |= QUIET;
                options ^= VERBOSE;
                break;
            case 'v':
                options |= VERBOSE;
                options ^= QUIET;
                break;
            case 'c':
                options ^= COLOR;
                break;
            case 't':
                options |= DATE;
                break;
            /* actions */
            case 'n':
                action = NEW;
                break;
            case 'x':
                action = DONE;
                break;
            case 'r':
                action = DELETE;
                break;
            case 's':
                action |= SHOW;
                break;
            /* groups */
            case 'g':
                todo->group = calloc((strlen(optarg)+1),sizeof(char));
                strncpy(todo->group,optarg,strlen(optarg));
                break;

            case '?':
                fprintf(stderr, "\t%s\n",optarg);
                errorcheck(FLAG_ERR);
                break;
        }
    }

    if (!action) action = SHOW;
    if (!todo->group) {
        todo->group = calloc(8,sizeof(char));
        strcpy(todo->group,"default");
    }

    if (action != SHOW && !args[optind]) errorcheck(CMD_ERR);

    /* rest of arguments become task */
    char *buf = calloc(LINE_MAX,sizeof(char));
    for (int j = optind; j < n; j++){
            strcat(buf,args[j]);
            strcat(buf,(j != n-1 ? " " : ""));
    }
    todo->note = calloc(strlen(buf)+1,sizeof(char));
    strncpy(todo->note, buf, strlen(buf));
    free(buf);

    return;
}

void errorcheck(ERROR err){
    /* if (errno != 0) { */
    /*     fprintf(stderr,"\nSYSTEM ERROR: %s\n",strerror(errno)); */
    /*     err |= SYS_ERR; */
    /* } */

    if (err == NO_ERR) return; 
    if (err & FLAG_ERR) fprintf(stderr,"ERROR: Unknown Flag, use -h for help\n");
    if (err & SQL_ERR) fprintf(stderr,"ERROR: SQL error\n");
    if (err & DIR_ERR) fprintf(stderr,"ERROR: Could not create $XDG_DATA_HOME/odot\n");
    if (err & ENV_ERR) fprintf(stderr,"ERROR: Could not access $HOME\n");
    if (err & EXIST_ERR) fprintf(stderr,"ERROR: Task already exists in group\n");
    if (err & NOEXIST_ERR) fprintf(stderr,"ERROR: Task could not be found in group\n");
    if (err & CMD_ERR) fprintf(stderr,"ERROR: No task given\n");

    exit(err);
}

void sqlerror(SQL db) {
    fprintf(stderr, "\n%s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    errorcheck(SQL_ERR);
}

void help(void){
    printf("Usage: odot [flags] (task)\n");
    printf("Option flags:\n");
    printf("\t-h\tthis help");
    printf("\t-V\tversion info");
    printf("\t-n\tadd new task");
    printf("\t-x\tmark task as done");
    printf("\t-s\tshow tasks");
    printf("\t-r\tremove task");
    printf("\t-a\tshow all groups");
    printf("\t-d\tshow finished tasks");
    printf("\t-A\tshow everything");
    printf("\t-c\tturn off colors");
    exit(0);
}

char *dbpath(void){
    char *dir = malloc(LINE_MAX * sizeof(char));

    /* set dir to $HOME/.local/share if XDG isn't set */
    if ((dir = getenv("XDG_DATA_HOME")) == NULL) {
        if ((dir = getenv("HOME")) == NULL) 
            errorcheck(ENV_ERR);
        strcat(dir,"/.local/share");
    }
    strcat(dir,"/odot");

    /* test if dir exists and create if it doesn't */
    DIR *test;
    if ((test = opendir(dir)) != NULL) {
        closedir(test);
    } else {
        if (mkdir(dir,0777) == SYS_ERR) errorcheck(DIR_ERR);
    }

    strcat(dir,"/odot.db");

    char *database = malloc((strlen(dir)+1) * sizeof(char));
    strncpy(database,dir,strlen(dir));
    /* free(dir); */

    return database;
}

void genhash(TASK todo) {
    u_int h=SEED;

    /* only want to combine for the length of shorter string */
    int g = strlen(todo->group);
    int n = strlen(todo->note);
    int len = (g <= n ? g : n);

    char *str = malloc(len*sizeof(char));

    for (int i = 0; i < len; i++)
        str[i] = todo->group[i] + todo->note[i];
    
    *str += todo->done;

    while (*str++)
        h = (~(h << 5) ^ *str) % TABLE_SIZE;

    todo->hash = h;
    
    return; 
}
