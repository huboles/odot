#include "odot.h"

enum color {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

int listcheck(void){
    char *s = malloc(MAXLINE * sizeof(char));

    fp = fopen(TODOLIST, "r");

    while (fgets(s, MAXLINE, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(note, s) == 0){
            free(s);
            return 1;
        }
    }
    free(s);
    return 0;
}

int geturgency(int n){
    if(n > 0 && n <= 10){
        if (n > 7)
            return RED;
        else if (n > 3)
            return YELLOW;
        else
            return GREEN;
    } else {
        printf("ERROR: urgency OUT OF RANGE");
        return -1;
    }
        
}

char *gettime(void){
    char *c = malloc(64*sizeof(char));
    time_t t = time(NULL);
    if (t == ((t) - 1)){
        error('t');
    }

    c = ctime(&t);

    if (c == NULL){
        error('t');
    }

    return c;


}
