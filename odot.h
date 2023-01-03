#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "sqlite3.h"

#define VERSION "0.2.1"
#define MAXLINE 10000
#define TABLE_SIZE 65535

/* sql commands */ 
#define BUILDTABLE "CREATE TABLE IF NOT EXISTS Tasks (Hash int NOT NULL PRIMARY KEY, Task varchar(10000) NOT NULL, Type varchar(32), Done int NOT NULL DEFAULT 0);"

#define INSERT "INSERT INTO Tasks VALUES"
#define DELETE "DELETE FROM Tasks WHERE Hash ="
#define DONE "UPDATE Tasks SET Done = 1 WHERE Hash ="
#define GETTASK "SELECT Task, Type, Hash FROM Tasks WHERE Task ="
#define CHANGEGROUP "UPDATE Tasks SET Type ="
#define PRINT "SELECT Done, Type, Task FROM Tasks WHERE Done = 0 ORDER BY Type;"
#define PRINTALL "SELECT Done, Type, Task FROM Tasks ORDER BY Type;"
#define PRINTGROUP "SELECT Done, Task FROM Tasks WHERE Done = 0 AND Type ="
#define PRINTGROUPALL "SELECT Done, Task FROM Tasks WHERE Type ="

/* error handling */
enum {SQLERR = 1, DIRERR = 1 << 1, ENVERR = 1 << 2, FLAGERR = 1 << 3, CMDERR = 1 << 4, GRPERR = 1 << 5};

/* main.c */
void error(int);
void help(void);
void parseopt(int, char **);

/* action.c */
void dbcheck(sqlite3 *db);
void newtask(sqlite3 *);
void done(sqlite3 *);
void update(sqlite3 *);
void removetask(sqlite3 *);
void show(sqlite3 *);

/* function.c */
char *filepath(void);
int genhash(char *);
void checksame(char *, char *);

/* functions for interfacing with sqlite database: database.c */
sqlite3 *accessdb(char *);
void sqlcmd(sqlite3 *, char *, char);
void sqlerror(sqlite3 *);
int printcallback(void *, int, char **, char **);
int groupcallback(void *, int, char **, char **);
int taskcallback(void *, int, char **, char **);
int checkcallback(void *, int, char **, char **);
