#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <dirent.h>

#include "sqlite3.h"

#define MAXLINE 10000

#define BUILDTABLE "CREATE TABLE IF NOT EXISTS Tasks (Hash int NOT NULL PRIMARY KEY, Task varchar(1000) NOT NULL, Type varchar(8), Done int NOT NULL DEFAULT 0);"

#define INSERT "INSERT INTO Tasks VALUES"
#define DELETE "DELETE FROM Tasks WHERE Hash ="
#define DONE "UPDATE Tasks SET Done = 1 WHERE Hash ="
#define GETTASK "SELECT Task, Type, Hash FROM Tasks WHERE Task ="
#define CHANGEGROUP "UPDATE Tasks SET Group ="
#define PRINT "SELECT Done, Type, Task FROM Tasks WHERE Done = 0 ORDER BY Type;"
#define PRINTALL "SELECT Done, Type, Task FROM Tasks ORDER BY Type;"
#define PRINTGROUP "SELECT Done, Task FROM Tasks WHERE Done = 0 AND Type ="
#define PRINTGROUPALL "SELECT Done, Task FROM Tasks WHERE Type ="

void error(int);
void help(void);
void parseopt(int, char**);
void operate(sqlite3 *);

/* action.c */
void newtask(sqlite3 *);
void done(sqlite3 *);
void update(sqlite3 *);
void removetask(sqlite3 *);
void show(sqlite3 *);

/* function.c */
char *filepath(void);
u_long genhash(void);
void checksame(char *,char *);

/* functions for interfacing with database: database.c */
sqlite3 *accessdb(char *);
void sqlcmd(sqlite3 *,char *,char);
void sqlerror(sqlite3 *);
int printcallback(void *,int,char **,char **);
int groupcallback(void *,int,char **,char **);
int taskcallback(void *,int,char **,char **);
