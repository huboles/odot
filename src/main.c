#include "odot.h"

ACTION action;
OPTIONS options = COLOR;


int main(int argc, char **argv){
    SQL db;
    SQL_ERROR sql_err = 0;

    char *path = dbpath();
    if ((sql_err = sqlite3_open(path,&db)) != SQLITE_OK)
        sqlerror(db);

    char *cmd = calloc(LINE_MAX+1,sizeof(char));
    sprintf(cmd,"CREATE TABLE IF NOT EXISTS Odot (Hash int NOT NULL PRIMARY KEY, Task varchar(%u) NOT NULL, Type varchar(%u), Done int NOT NULL DEFAULT 0, Date int NOT NULL);", LINE_MAX,GROUP_MAX);
    if ((sql_err = sqlite3_exec(db,cmd,NULL,0,NULL)) != SQLITE_OK)
        sqlerror(db);
    free(cmd);

    TASK todo =  buildtask();
    parseopts(argc,argv,todo);

    genhash(todo);
    int count = dbcheck(db,todo);

    switch (action){
        case NEW:
            if (count == 0) {
                newtask(db,todo);
            } else {
                errorcheck(EXIST_ERR);
            }
            break;
        case DONE:
            if (count == 1) {
                done(db,todo);
            } else {
                errorcheck(NOEXIST_ERR);
            }
            break;
        case DELETE:
            if (count == 1) {
                removetask(db,todo);
            } else {
                errorcheck(NOEXIST_ERR);
            }
            break;
    }

    /* show db after action */
    if (action & SHOW){
        show(db,todo);
    }

    freetask(todo);
    sqlite3_close(db);
    return 0;
}

