#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXLINE 1000
#define TIME "%H:%M %m-%d-%y"
#define TODOLIST "/home/huck/.local/state/odot/todo"

struct task {
    char *task;
    int date;
    char *group;
};

char *getnote(int, char *[]);
void getopt(int, char *[]);

void add(struct task, int);
void rem(void);
void show(void);

int listcheck(struct task);
int geturgency(int);
char *gettime(void);

void error(char);

int linecount(void);
void dialogue(char *, char *, int);

struct task maketask(char *, char *);
void puttask(struct task n);
struct task gettask(void);

char *note, *o;
int urgency;
FILE *fp;

