#include "odot.h"

extern OPTIONS options;

void newtask(SQL db,TASK todo){
    char *cmd = malloc(LINE_MAX*sizeof(char));
    SQL_ERROR err;

    sprintf(cmd,"INSERT INTO Odot VALUES (%lu, '%s', '%s', 0, %lu);",todo->hash,todo->note,todo->group,todo->date);
    if ((err = sqlite3_exec(db, cmd, NULL, NULL, NULL)) != SQLITE_OK)
        sqlerror(db);

    free(cmd);
    return;
}

void done(SQL db, TASK todo){
    char *cmd = malloc(LINE_MAX*sizeof(char));
    SQL_ERROR err;

    sprintf(cmd,"UPDATE Odot SET Done = 1 WHERE Hash = %lu;", todo->hash);
    if ((err = sqlite3_exec(db, cmd, NULL, NULL, NULL)) != SQLITE_OK)
        sqlerror(db);
    

    free(cmd);
    return;
}

void removetask(SQL db, TASK todo){
    char *cmd = malloc(LINE_MAX*sizeof(char));
    SQL_ERROR err;

    sprintf(cmd,"DELETE FROM Odot WHERE Hash = %lu;",todo->hash);
    if ((err = sqlite3_exec(db, cmd, NULL, NULL, NULL)) != SQLITE_OK)
        sqlerror(db);
    
    free(cmd);
    return;
}

void show(SQL db, TASK todo){
    char *cmd = malloc(LINE_MAX*sizeof(char));
    SQL_ERROR err;

    if (options & COLOR) {
        printf("\n  \033[35;1mTODO\033[0m: \n");
    } else {
        printf("\n  TODO: \n");
    }

    
    /* building sql command from options */
    if (options & SHOWDONE && options & SHOWALL){
        sprintf(cmd,"SELECT * FROM Odot;");
    } else if (options & SHOWALL){
        sprintf(cmd, "SELECT * FROM Odot WHERE Done = 0;");
    } else if (options & SHOWDONE){
        sprintf(cmd, "SELECT * FROM Odot WHERE Type = '%s';", todo->group);
    } else {
        sprintf(cmd, "SELECT * FROM Odot WHERE Type = '%s' AND Done = 0;",todo->group);
    }

    if ((err = sqlite3_exec(db, cmd, sql_print, NULL, NULL)) != SQLITE_OK)
        sqlerror(db);

    free(cmd);
    return;
}

int dbcheck(SQL db,TASK todo){
    SQL_ERROR err;
    char *cmd = malloc(LINE_MAX*sizeof(char));
    int *count = malloc(sizeof(int));
    *count = 0;

    sprintf(cmd,"SELECT * FROM Odot WHERE Hash = %lu;",todo->hash);

    if ((err = sqlite3_exec(db, cmd, sql_count, count, NULL)) != SQLITE_OK)
        sqlerror(db);

    free(cmd);
    return *count;
}
