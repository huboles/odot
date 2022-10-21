#include "todo.h"

char *note, *o;

int main(int argc, char *argv[]){
    char op;
    int length,i;
    note = (char *) malloc(MAXLINE * sizeof(char));
    o = (char *) malloc (3 * sizeof(char));

    getnote(argc, argv);
    length = strlen(note)+1;
    getopt(argc, argv);
    
    for (i = 0; i < strlen(o); i++)
        switch (o[i]) {
            case 'n':
                if (listcheck() == 0){
                    add();
                    printf("\033[32mAdded to list\033[0m: %s\n", note);
                } else {
                    printf("\033[33mAlready on list\033[0m: %s\nRemove from list? (y/\033[1mn\033[0m): ", note);
                    if (getchar() == 'y') 
                        rem();
                }
                break;
            case 'd':
                if (listcheck() == 1) {
                    rem();
                    printf("\033[36mRemoved from list\033[0m: %s\n", note);
                } else {
                    printf("\033[31mNot on list\033[0m: %s\nAdd to list? (y/\033[1mn\033[0m): ", note);
                    if (getchar() == 'y') 
                        add();
                }
                break;
            case 's':
                printf("\n\tTODO LIST:\n");
                show();
                break;
        }
    free(note); 
    return 0;
}

