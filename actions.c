#include "odot.h"

extern char *task,
            *group,
            *newgroup;

extern u_long hash;

extern int exists,showall,showdone;

void newtask(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    sprintf(cmd,"%s '%s';",GETTASK,task);
    sqlcmd(db,cmd,'c');

    if (exists == 0){
        sprintf(cmd,"%s (%lu, '%s', '%s', 0);",INSERT,hash,task,group);
        sqlcmd(db,cmd,'q');
    }
    return;
}

void done(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    sprintf(cmd,"%s '%s';",GETTASK,task);
    sqlcmd(db,cmd,'c');


    if (exists == 1) {
        sprintf(cmd,"%s %lu;",DONE,hash);
        sqlcmd(db,cmd,'q');

        sprintf(cmd,"%s %lu;", GETTASK,hash);
        sqlcmd(db,cmd,'t');

        sprintf(cmd,"SELECT Done, Task FROM Tasks WHERE Hash = %lu",hash);
        printf("\n");
        sqlcmd(db,cmd,'p');
    }
    return;
}

void update(sqlite3 *db){

}

void removetask(sqlite3 *db){
    char *cmd = malloc(MAXLINE*sizeof(char));

    sprintf(cmd,"%s '%s';",GETTASK,task);
    sqlcmd(db,cmd,'c');

    if (exists == 1){
        sprintf(cmd,"%s %lu;",DELETE,hash);
        sqlcmd(db,cmd,'c');
    }
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
    return;
}
