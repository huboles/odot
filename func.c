#include "odot.h"

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

    /* Returns:
        0 - Nothing matches
        1 - Task matches
        2 - Group matches
        3 - Both match
    */
int listcheck(struct task t, FILE *fp){
    int i;
    i += (strcmp(t.task,gettask(fp).task) == 0) ? 1 : 0;
    i += (strcmp(t.group,gettask(fp).group) == 0) ? 2 : 0;
    return i;
}


char *gettime(void){
    return NULL;
}

int linecount(FILE *fp){
    int i = 0;
    char c;
    while ((c = fgetc(fp)) != EOF){
        if (c == '\n')
            i++;
    }
    fseek(fp,0,SEEK_SET);
    return i;
}
