#include "odot.h"

extern char *task,
            *group,
            *newgroup;

extern int hash;

extern int  exists,
            showall,
            showdone;

void newtask(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    if (exists == 0){
        sprintf(cmd,"%s (%i, '%s', '%s', 0);",INSERT,hash,task,group);
        sqlcmd(db,cmd,'q');
    } else {
        printf("Task already exists\nMark as done? [y/(n)] ");
        if (getchar() != 'n') done(db);
    }
    free(cmd);
    return;
}

void done(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    if (exists == 1) {
        sprintf(cmd,"%s %i;",DONE,hash);
        sqlcmd(db,cmd,'q');

        sprintf(cmd,"%s %i;", GETTASK,hash);
        sqlcmd(db,cmd,'t');

        printf("\n");
        sprintf(cmd,"SELECT Done, Task FROM Tasks WHERE Hash = %i;",hash);
        sqlcmd(db,cmd,'p');
    } else {
        printf("Task does not exist\nAdd task [y/n] ");
        if (getchar() != 'n') newtask(db);
    }

    free(cmd);
    return;
}

void update(sqlite3 *db){
    /* terminates if newgroup isn't set*/
    if (strcmp(newgroup,"") == 0) error(GRPERR);
    char *cmd = malloc(MAXLINE*sizeof(char));

    if (exists == 1) {
        sprintf(cmd,"%s '%s' WHERE Hash = %i;",CHANGEGROUP,newgroup,hash);
        sqlcmd(db,cmd,'q');
        strcpy(group,newgroup);
    } else {
        printf("Task does not exist\nAdd task [y/n] ");
        if (getchar() != 'n') newtask(db);
    }
    free(cmd);
    return;
}

void removetask(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    if (exists == 1){
        sprintf(cmd,"%s %i;",DELETE,hash);
        sqlcmd(db,cmd,'c');
    }
    free(cmd);
    return;
}

void show(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));
    int mask = showall + (showdone << 1);

    printf("\n\t\033[35;1mTODO\033[0m: \033[36m%s\033[0m\n\n",group);

    switch (mask) {
        case 0:
            sprintf(cmd,"%s '%s';",PRINTGROUP,group);
            sqlcmd(db,cmd,'p');
            break;
        case 1:
            sqlcmd(db,PRINT,'p');
            break;
        case 2:
            sprintf(cmd,"%s '%s' ORDER BY Done;",PRINTGROUPALL,group);
            sqlcmd(db,cmd,'p');
            break;
        case 3:
            sqlcmd(db,PRINTALL,'p');
            break;
    }
    free(cmd);
    return;
}

void dbcheck(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    sprintf(cmd,"%s '%s';",GETTASK,task);
    sqlcmd(db,cmd,'c');

    free(cmd);
    return;
}
