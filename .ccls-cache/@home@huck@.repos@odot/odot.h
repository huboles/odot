#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXLINE 1000
#define TIME "%H:%M %m-%d-%y"
#define TODOLIST "/home/huck/.local/state/odot/todo"

struct task {
    int length;
    char *task;
    char *date;
    char *due;
    int urgency;
};

char *getnote(int, char *[]);
void getopt(int, char *[]);

void add(void);
void rem(void);
void show(void);

int listcheck(struct task);
int geturgency(int);
char *gettime(void);

void error(char);

struct task maketask(int n, char **arg);
void puttask(struct task n, FILE *fp);
struct task gettask(FILE *fp);

char *note, *o;
int urgency;
FILE *fp;

