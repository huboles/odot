#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXLINE 1000
#define TIME "%H:%M %m-%d-%y"
#define TODOLIST "/home/huck/.local/state/odot/todo"

char *getnote(int, char *[]);
void getopt(int, char *[]);
void add(void);
void rem(void);
void show(void);
int listcheck(void);
int geturgency(int);

void error(char);

char *note, *o;
int urgency;
FILE *fp;

