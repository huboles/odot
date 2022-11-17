#include "odot.h"

void add(struct task t, FILE *fp){
                    printf("\talloc\n");
    char *line = malloc(MAXLINE*sizeof(char));
                    printf("\tfopen\n");
    FILE *buf = fopen("/home/huck/.local/state/odot/odot.txt", "w+");
    int i = 0;
    
                    printf("\tNULLcheck\n");
    if (fgets(line,MAXLINE,fp) == NULL){
        puttask(t,buf);
    } else {
                        printf("\tloopstart\n");
                        int j = 0;
        while (fgets(line,MAXLINE,fp) != NULL){
                        printf("\t%i-nloop\n", ++j);
            switch (listcheck(t,line)){
                case 3:
                    dialogue("Already on todo list", t.task, CYAN);
                    printf("Remove from list?");
                    if (check() == 0){
                        break;
                    } else {
                        puttask(gettask(line), buf);
                        break;
                    }
                case 1:
                    dialogue("Already on list in a different group", gettask(line).group, YELLOW);
                    if (check() == 0){
                        puttask(t,buf);
                        i++;
                    }
                    puttask(gettask(line), buf);
                    break;
                default:
                    /* first time t.task is lexigraphically greater than a previous task */
                    if (i == 0 && strcmp(line,t.task) > 0){
                        puttask(t,buf);
                        ++i;
                    }
                    puttask(gettask(line), buf);
                    break;
            }
        }
    }

    fclose(fp);
    fclose(buf);
    remove("/home/huck/.local/state/odot/todo.txt");
    rename("/home/huck/.local/state/odot/odot.txt", "/home/huck/.local/state/odot/todo.txt");
    free(line); 
    fp = fopen("/home/huck/.local/state/odot/todo.txt", "w+");
    if (!fp)
        error(1);
    return; 
}


void rem(struct task t, FILE *fp){
    char *s = malloc(MAXLINE * sizeof(char));
    FILE *buf = fopen("/home/huck/.local/state/odot/odot.txt", "w+");
    int i = 0;

    while (fgets(s, MAXLINE, fp) != NULL){
        s[strlen(s) - 1] = 0;
        if (strcmp(t.task, s) != 0){
            fputs(strcat(s,"\t"),buf);
        } else {
            i++;
        }
    }

    fclose(fp);
    fclose(buf);

    remove ("/home/huck/.local/state/odot/todo.txt");
    rename("/home/huck/.local/state/odot/odot.txt", "/home/huck/.local/state/odot/todo.txt");

    fp = fopen("/home/huck/.local/state/odot/todo.txt", "w+");

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
    char *task = malloc(MAXLINE * sizeof(char));
    struct task tmp;

                printf("\twhileloop\n");
                int j = 0;

    while ((fgets(task, MAXLINE, fp)) != NULL ){
                printf("\t%i-nloop\n", ++j);
            tmp = gettask(task);
        if (strcmp(group, "all") == 0 || strcmp(tmp.group, group) == 0){
            formattask(tmp);
        }
    }
    free(task);
}

