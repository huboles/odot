#include "odot.h"

void add(struct task t){
    char *line = malloc(MAXLINE*sizeof(char));  printf("\talloc\n");
    FILE *fp = fopen("/home/huck/.local/state/odot/todo.txt", "r");
    FILE *buf = fopen("/home/huck/.local/state/odot/odot.txt", "w+");   printf("\tfopen\n");
    int i = 0;
    
    if (fgets(line,MAXLINE,fp) == NULL){        printf("\tNULLcheck\n");
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
                        puttask(*gettask(line), buf);
                        break;
                    }
                case 1:
                    dialogue("Already on list in a different group", gettask(line)->group, YELLOW);
                    if (check() == 0){
                        puttask(t,buf);
                        i++;
                    }
                    puttask(*gettask(line), buf);
                    break;
                default:
                    /* first time t.task is lexigraphically greater than a previous task */
                    if (i == 0 && strcmp(line,t.task) > 0){
                        puttask(t,buf);
                        ++i;
                    }
                    puttask(*gettask(line), buf);
                    break;
            }
        }
    }

    fclose(fp);
    fclose(buf);
    rename("/home/huck/.local/state/odot/odot.txt", "/home/huck/.local/state/odot/todo.txt");
    fp = fopen("/home/huck/.local/state/odot/todo.txt", "w+");
    if (!fp)
        error(1);
    return; 
}


void rem(struct task t){
    char *s = malloc(MAXLINE * sizeof(char));
    FILE *fp = fopen("/home/huck/.local/state/odot/todo.txt", "r");
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

    if (i == 0){
        dialogue("Task not found", t.task, YELLOW);
        printf("Add to list?");
        if(check() == 0){
            add(t);
        }
    }
}

void show(char *group){
    char *task = malloc(MAXLINE * sizeof(char));
    FILE *f = fopen("/home/huck/.local/state/odot/todo.txt", "r");
    struct task tmp;

                printf("\twhileloop\n");
                int j = 0;
    while ((fgets(task, MAXLINE, f)) != NULL ){
            tmp = *gettask(task);        printf("\t%i-nloop\n", ++j);
        if (strcmp(group, "all") == 0 || strcmp(tmp.group, group) == 0){
            formattask(tmp);
        }
    }
    fclose(f);
}

