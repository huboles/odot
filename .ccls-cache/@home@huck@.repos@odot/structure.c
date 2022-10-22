#include "odot.h"

extern int urgency;
extern FILE *fp;

struct note {
    int length;
    char *note;
    int date;
    int due;
    int urgency;
};

struct note makenote(int n, char **arg){
    struct note temp;

    temp.note = getnote(n,arg);
    temp.length = strlen(temp.note);
    temp.date = 0;
    temp.due = 0;
    temp.urgency = urgency;

    return temp;
}

void putnote(struct note n){
    fp = fopen(TODOLIST, "w");

    if (fp == NULL){
        printf("ERROR: COULD NOT OPEN FILE %s\n", TODOLIST);
    }

    fprintf(fp, "%i\t%s\t%i\t%i\t%i\n",n.length,n.note,n.date,n.due,n.urgency);
    
}

struct note findnote(char *c){
    struct note tmp;
    
    sscanf(c,"%i\t%s\t%i\t%i\t%i\n",&tmp.length,tmp.note,&tmp.date,&tmp.due,&tmp.urgency);

    return tmp;
}
