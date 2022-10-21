#include "todo.h"

extern char *note, *o;

void getnote(int n, char *arg[]){
    char *s = malloc(MAXLINE * sizeof(char));

    while(--n > 0){
        if ((*++arg)[0] != '-'){
            strcat(s, *arg);
            strcat(s, (n > 1) ? " " : "");
        }
    }
    strcpy(note, s);
    free(s);
}

void getopt(int n, char *arg[]){
    char *c;

    if (n == 1){
        o = "s";
    }

    while (--n > 0 && (*++arg)[0] == '-'){
        if (strlen(*arg) <= 3){
            c = malloc(strlen(*arg) * sizeof(char));
            c = *arg;
            strcat(o,(strchr(c, 'd')) ? "d" : "n");
            if (strchr(c,'s') != NULL){
                strcat(o,"s");
            }
            free(c);
        } else {
            printf("\033[31mToo many options\033[0m: %s\n\tUse -h for help", *arg);
        }
    }

    if (strlen(o) == 0){
        if (listcheck() == 0)
            o = "n";
        else
            o = "d";
    }
}


