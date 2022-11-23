#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 500
#define LIST    "/home/huck/.local/state/odot/todo.txt"
#define DONE    "/home/huck/.local/state/odot/done.txt"
#define TMP    "/home/huck/.local/state/odot/odot.txt"

int getopt(int, char **);
char *getnote(int, char **);

void addnote(char *);
void show();

int main(int argc, char *argv[]){

    if (argc == 1){
        show();
    } else {
        addnote(getnote(argc,argv));
    }
    return 0;
}

char *getnote(int n, char *arg[]){
    char *s = malloc(MAXLINE * sizeof(char));
    while (--n > 0){
        strcat(s,*++arg);
        strcat(s,(n > 1) ? " " : "\n");
    }
    return s;
}

void addnote(char *note){
    int i = 0;
    char *buf = malloc(MAXLINE * sizeof(char));

    FILE *fp = fopen(LIST,"r");
    FILE *fdone = fopen(DONE,"a");
    FILE *tmp = fopen(TMP,"w");
    if(!fp || !tmp || !fdone)
        exit(1);

    while(fgets(buf, MAXLINE, fp)){
        if (strcmp(note,buf) > 0){
            fputs(buf,tmp);
        } else if (strcmp(note,buf) == 0){
            fputs(note,fdone);
            printf("Removed from list: %s", note);
            i++;
        } else if (strcmp(note,buf) < 0){
            if (i == 0){
                fputs(note,tmp);
                printf("Added to list: %s", note);
                i++;
            }
            fputs(buf,tmp);
        }
    }
    if (i == 0){
        fputs(note,tmp);
        printf("Added to list: %s", note);
    }

    fclose(tmp);
    fclose(fp);
    fclose(fdone);
    free(buf);
    remove(LIST);
    rename(TMP,LIST);
    return;
}

void show(void){
    FILE *fp = fopen(LIST,"r");
    char *buf = malloc(MAXLINE * sizeof(char));

    printf("\033[36;1mTODO\033[0m:\n");
    while(fgets(buf,MAXLINE,fp)){
       printf("    \033[35;1m*\033[0m %s", buf);
    }

    free(buf);
    fclose(fp);
    return;
}

