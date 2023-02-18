#include "odot.h"

extern OPTIONS options;

int sql_print(void *v,int num, char **sql, char **cols){
    static char *group;
    if (!group) group = calloc(GROUP_MAX+1,sizeof(char));

    TASK tmp = buildtask();
    filltask(tmp,sql);

        /* print group if it changes */
    if (options & SHOWALL && strcmp(tmp->group,group) != 0) {
        printf("\n\t\033[34m%s\033[0m\n",tmp->group);
        strncpy(group,tmp->group,strlen(tmp->group));
    }

    printtask(tmp);
    freetask(tmp);
    return 0;
}

int sql_get(void *todo,int argc, char **sql, char **cols){
    TASK tmp = (TASK) todo;
    filltask(tmp, sql);
    return 0;
}

int sql_count(void *count,int argc, char **sql, char **cols){
    int *tmp = (int *) count;
    (*tmp)++;
    return 0;
}
