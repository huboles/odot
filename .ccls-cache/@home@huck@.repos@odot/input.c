#include "odot.h"

extern char *note, *o;
extern int urgency;

char *getnote(int n, char *arg[]){
    char *s = malloc(MAXLINE * sizeof(char));

    while(--n > 0){
        if ((*++arg)[0] != '-'){
            strcat(s, *arg);
            strcat(s, (n > 1) ? " " : "");
        }
    }
    return s;
}

void getopt(int n, char *arg[]){
    char *c;

    if (n == 1){
        o = "s";
        return;
    }
    
    while (--n > 0 && (*++arg)[0] == '-'){
        c = malloc(strlen(*arg) * sizeof(char));
        c = *arg;
        strcat(o,(strchr(c, 'd')) ? "d" : "n");

        if (strchr(c,'s') != NULL){
            strcat(o,"s");
        }

        if (strchr(c,'i') != NULL){
            if (isdigit((int) *++arg)){
                urgency = (int) *arg;
            } else {
                printf("Non-integer argument for -i: %s\n", *arg);
            }
        } else {
            urgency = 5;
        }
        free(c);
    }

    if (strlen(o) == 0)
        o = (listcheck() == 0) ? "n" : "d";
}

