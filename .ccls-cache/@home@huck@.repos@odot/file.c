#include "odot.h"

void add(struct task t, FILE *fp){
                    printf("\nalloc\n");
    char *c = malloc(strlen(t.task)*sizeof(char));
                    printf("\nfopen\n");
    FILE *buf = fopen("odot.tmp", "w");
    int i = 0;
    
                    printf("\nloopstart\n");
                    int j = 0;
    while (fgets(c,strlen(t.task),fp) != NULL){
                    printf("\n%i-nloop\n", j++);
        switch (listcheck(t,fp)){
            case 3:
                dialogue("Already on todo list", t.task, CYAN);
                printf("Remove from list?");
                if (check() == 0){
                    break;
                } else {
                    puttask(gettask(fp), buf);
                    break;
                }
            case 1:
                dialogue("Already on list in a different group", gettask(fp).group, YELLOW);
                if (check() == 0){
                    puttask(t,buf);
                    i++;
                }
                puttask(gettask(fp), buf);
                break;
            default:
                /* first time t.task is lexigraphically greater than a previous task */
                if (i == 0 && strcmp(c,t.task) > 0){
                    puttask(t,buf);
                    ++i;
                }
                puttask(gettask(fp), buf);
                break;
        }
    }

    free(c);
    fclose(fp);
    fclose(buf);
    remove("/home/huck/.local/state/odot/todo");
    rename("odot.tmp", "/home/huck/.local/state/odot/todo");
    return; 
}


void rem(struct task t, FILE *fp){
    char *s = malloc(MAXLINE * sizeof(char));
    FILE *buf = fopen("odot.tmp", "w");
    int i = 0;

    while (fgets(s, MAXLINE, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(t.task, s) != 0){
            fputs(strcat(s,"\n"),buf);
        } else {
            i++;
        }
    }

    fclose(fp);
    fclose(buf);

    remove ("/home/huck/.local/state/odot/todo");
    rename("odot.tmp", "/home/huck/.local/state/odot/todo");

    if (i == 0){
        dialogue("Task not found", t.task, YELLOW);
        printf("Add to list?");
        if(check() == 0){
            add(t,fp);
        }
    }

    free(s);
}

void show(char *group, FILE *fp){
    char *c = malloc(sizeof(char));

    while (fgets(c, 1, fp) != NULL ){
        if (strcmp(group, "all") == 0 || strcmp(gettask(fp).group, group) == 0){
            formattask(gettask(fp));
        }
    }
    free(c);
}

