#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "sqlite3.h"

#define MAXLINE 10000

struct task {
    char        *task;
    char        *group;
};


void parseopt(int, char**);
void operate(char *, struct task, sqlite3 *);
struct task maketask(char *, char *);

/* functions for interfacing with database: database.c */
sqlite3 *accessdb(char *);
void buildtables(sqlite3 *);
void addtask(sqlite3 *, struct task);
void removetask(sqlite3 *, struct task);
void donetask(sqlite3 *, struct task);
int printcallback(void *,int,char **,char **);
void print(sqlite3 *);
void printdone(sqlite3 *);
void printgroup(sqlite3 *, struct task);
void printgroupdone(sqlite3 *, struct task);
