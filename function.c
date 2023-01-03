#include "odot.h"

extern char *group,
            *newgroup,
            *task,
            *action;

extern u_long hash;

extern int exists;

u_long genhash(void){
    char *tmp = calloc((strlen(task)+strlen(group)+1), sizeof(char));
    strcat(tmp,task);
    strcat(tmp,group);
    int h = 11235813;

    for (int i = 0; i < strlen(tmp);i++)
        h = ~((h << 5) ^ tmp[i]);

    return h;
}

char *filepath(void){
    char *dir = getenv("XDG_DATA_HOME");
    char *db = malloc(MAXLINE * sizeof(char));

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

    sprintf(db,"%s/odot.db",dir);

    return db;
}

void checksame(char *task,char *oldgroup){
    printf("\033[32m%s\033[0m already exists, but in \033[34m%s\033[0m\nIs this the same task? [y/\033[1mn\033[0m] ",task,oldgroup);

    if (getchar() == 'y'){
        exists = 1; 
        strcpy(group,oldgroup); 
        hash = genhash();
    } 

    return;
}
