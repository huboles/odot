#include "odot.h"

extern char *group,
            *newgroup,
            *task,
            *action;

extern int hash;

extern int exists;

/* dgb hash */
int genhash(char *str) {
    u_int h=5381;
    
    for (int i = 0; i < (int) strlen(str); i++) {
        h = ((h << 5) + h) + *str++;
    }
    
    return h % TABLE_SIZE;
}

char *filepath(void){
    char *dir = getenv("XDG_DATA_HOME");
    char *database = malloc(MAXLINE * sizeof(char));

    /* set dir to $HOME/.local/share if XDG isn't set */
    if (!dir) {
        dir = getenv("HOME");    
        if (!dir) error(ENVERR);
        strcat(dir,"/.local/share");
    }
    strcat(dir,"/odot");

    DIR *test = opendir(dir);

    /* test if dir exists and create if it doesn't */
    if (test) {
        closedir(test);
    } else {
        int err = mkdir(dir, 0777);
        if (err) error(DIRERR);
    }

    sprintf(database,"%s/odot.db",dir);
    free(dir);

    return database;
}

void checksame(char *task,char *oldgroup){
    printf("\033[32m%s\033[0m already exists, but in \033[34m%s\033[0m\nIs this the same task? [y/\033[1mn\033[0m] ",task,oldgroup);

    if (getchar() == 'y'){
        exists = 1; 
        strcpy(group,oldgroup); 
        char *hashstring = malloc((strlen(task)+strlen(group)+1)*sizeof(char));
        strcpy(hashstring, task);
        strcat(hashstring,group);
        hash = genhash(hashstring);
        free(hashstring);
    } 

    return;
}
