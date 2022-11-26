#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 500

int getopt(int, char **);
char *getnote(int, char **);
void envar(void);

void addnote(char *);
void show();

char *list;
char *done;
char *tmp;

int main(int argc, char *argv[]){
    extern char *list;
    extern char *done;
    extern char *tmp;

    char *homedir = getenv("HOME");

    list = malloc((strlen(homedir)+22)*sizeof(char));
    done = malloc((strlen(homedir)+22)*sizeof(char));
    tmp = malloc((strlen(homedir)+21)*sizeof(char));

    sprintf(list,"%s/.local/state/odot/todo.txt",homedir);
    sprintf(done,"%s/.local/state/odot/done.txt",homedir);
    sprintf(tmp,"%s/.local/state/odot/tmp.txt",homedir);

    if (argc == 1){
        show();
    } else {
        addnote(getnote(argc,argv));
    }

    free(tmp);
    free(done);
    free(list);
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
    extern char *list;
    extern char *done;
    extern char *tmp;

    int i = 0;
    char *buf = malloc(MAXLINE * sizeof(char));

    FILE *fp = fopen(list,"r");
    FILE *fdone = fopen(done,"a");
    FILE *tfp = fopen(tmp,"w");
    if(!fp || !tmp || !fdone)
        exit(1);

    while(fgets(buf, MAXLINE, fp)){
        if (strcmp(note,buf) > 0){
            fputs(buf,tfp);
        } else if (strcmp(note,buf) == 0){
            fputs(note,fdone);
            printf("Removed from list: %s", note);
            i++;
        } else if (strcmp(note,buf) < 0){
            if (i == 0){
                fputs(note,tfp);
                printf("Added to list: %s", note);
                i++;
            }
            fputs(buf,tfp);
        }
    }
    if (i == 0){
        fputs(note,tfp);
        printf("Added to list: %s", note);
    }

    fclose(tfp);
    fclose(fp);
    fclose(fdone);
    free(buf);
    remove(list);
    rename(tmp,list);
    return;
}

void show(void){
    extern char *list;

    FILE *fp = fopen(list,"r");
    char *buf = malloc(MAXLINE * sizeof(char));

    printf("\033[36;1mTODO\033[0m:\n");
    while(fgets(buf,MAXLINE,fp)){
       printf("    \033[35;1m*\033[0m %s", buf);
    }

    free(buf);
    fclose(fp);
    return;
}

