#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define TODOLIST "/home/huck/.local/state/odot/todo"

#define MAXLINE 1000
#define TIME "%H:%M %m-%d-%y"

struct task {
    char *task;
    char *group;
};

struct task getnote(int, char *[], char *);
short getopt(int, char *[]);

void add(struct task, FILE *);
void rem(struct task, FILE *);
void show(char *group, FILE *);

int listcheck(struct task, char *);
int geturgency(int);
char *gettime(void);

void dialogue(char *, char *, int);
void formattask(struct task t);
void error(int);
int check(void);

struct task maketask(char *, char *);
void puttask(struct task n, FILE*);
struct task gettask(char *);

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
