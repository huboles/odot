#include "odot.h"

int main(int argc, char *argv[]){
                printf("\nstart\n");
    struct task note;
    short opt;
    FILE *fp;
    char *group = malloc(MAXLINE*sizeof(char));

                printf("\nfopen\n");
    fp = fopen("/home/huck/.local/state/odot/todo", "w+");
    if (!fp){
        error(1);
    }

                printf("\ngetopt\n");
    opt = getopt(argc, argv);

                printf("\ngetnote\n");
    note = getnote(argc, argv, group);

    if (opt >= 4){
                printf("\nrem\n");
        rem(note, fp);
    } else {
                printf("\nadd\n");
        add(note, fp);
    }

    if (opt % 2 != 0){
                printf("\nshow\n");
        show(group, fp); 
    }

    free(group);
    fclose(fp);
    return 0;
}

void error(int err){
    switch (err) {
        case 1:
            fprintf(stderr,"ERROR: COULD NOT ACCESS FILE: %s\n", "/home/huck/.local/state/odot/todo");
            break;
        case 2:
            fprintf(stderr,"ERROR: CANT ADD AND REMOVE SAME TASK\n");
            break;
    }
    exit(err);
}

void dialogue(char *m1, char *m2, int c){
    printf("\033[1;3%im%s\033[0m: %s\n", c, m1, m2);
    return;
}

void formattask(struct task t){
    printf("* %s\t%s\t%i", t.task, t.group, t.date);
}

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

/* returns 0 for yes and 1 for no */
int check(void){
    printf("Continue? [y/n] (y):");
    if (((char) getchar()) == 'n')
        return 1;
    return 0;
}
