#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include "sqlite3.h"

#define VERSION "0.3.0"

#define LINE_MAX 10000
#define GROUP_MAX 256

#define SEED 11235813
#define TABLE_SIZE 65535

typedef int ERROR;
enum {
    NO_ERR      = 0,
    SYS_ERR     = 1 << 0,
    SQL_ERR     = 1 << 1,
    ENV_ERR     = 1 << 2,
    FLAG_ERR    = 1 << 3,
    CMD_ERR     = 1 << 4,
    GROUP_ERR   = 1 << 5,
    DIR_ERR     = 1 << 6,
    EXIST_ERR   = 1 << 7,
    NOEXIST_ERR = 1 << 8 
};

typedef u_int8_t OPTIONS;
enum {
    SHOWALL     = 1 << 0,
    SHOWDONE    = 1 << 1,
    QUIET       = 1 << 2,
    VERBOSE     = 1 << 3,
    DATE        = 1 << 4,
    COLOR       = 1 << 5
};

typedef u_int8_t ACTION;
enum {
    NEW     = 1 << 0,
    DONE    = 1 << 1,
    DELETE  = 1 << 2,
    SHOW    = 1 << 3
};

typedef sqlite3 * SQL;
typedef int       SQL_ERROR;
typedef u_int8_t  SQL_ACTION;
enum {
    ADD     = 1 << 0,
    PRINT   = 1 << 1,
    COMMAND = 1 << 2,
    CHECK   = 1 << 3
};

typedef struct task *TASK;
struct task {
    u_int64_t  hash;
    char      *note;
    char      *group;
    int8_t     done;
    int8_t     in_db;
    time_t     date;
};

/* func.c */
void parseopts(int, char **, TASK);
void errorcheck(ERROR);
void sqlerror(SQL);
void help(void);
char *dbpath(void);
void genhash(TASK);

/* actions.c */
void newtask(SQL,TASK);
void done(SQL,TASK);
void removetask(SQL,TASK);
void show(SQL,TASK);
int dbcheck(SQL,TASK);

/* struct.c */
TASK buildtask(void);
void freetask(TASK);
void printtask(TASK);
void filltask(TASK,char **);

/* database.c */
int sql_print(void *, int, char **, char **);
int sql_get(void *, int, char **, char **);
int sql_count(void *, int, char **, char **);
