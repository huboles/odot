#include "odot.h"

sqlite3 *accessdb(char *file){
    sqlite3 *db;

    int err = sqlite3_open(file, &db);
    if (err) {
        fprintf(stderr, "Could not open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    return db;
}

void buildtables(sqlite3 *db){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"CREATE TABLE IF NOT EXISTS Tasks (Task varchar(1000) NOT NULL PRIMARY KEY, Type varchar(100) NOT NULL, Done int NOT NULL DEFAULT 0);");
    int err = sqlite3_exec(db,cmd,NULL,NULL,errmsg);
    if (err) {
        fprintf(stderr, "Could not create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}


void addtask(sqlite3 *db, struct task task){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"INSERT INTO Tasks VALUES ( '%s', '%s', 0);",task.task,task.group);
    int err = sqlite3_exec(db,cmd,NULL,NULL,errmsg);
    if (err) {
        fprintf(stderr, "Could not add task: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    free(cmd);
    return;
}

void removetask(sqlite3 *db, struct task task){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"DELETE FROM Tasks WHERE Task = '%s';",task.task);
    int err = sqlite3_exec(db,cmd,NULL,NULL,errmsg);
    if (err) {
        fprintf(stderr, "Could not remove task: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}

void donetask(sqlite3 *db, struct task task){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"UPDATE Tasks SET Done = 1 WHERE Task = '%s';",task.task);
    int err = sqlite3_exec(db,cmd,NULL,NULL,errmsg);
    if (err) {
        fprintf(stderr, "Could not modify task in db: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}

int printcallback(void *unused,int argc, char **argv, char **name){
    printf("\t[%s] - ", (strcmp(argv[0],"1") == 0) ? "X" : " ");
    for (int i = 1; i < argc; i++){
        printf("%s\t",argv[i]);
    }
    printf("\n");
    return 0;
}

void print(sqlite3 *db){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"SELECT Done, Type, Task FROM Tasks WHERE Done = 0 ORDER BY Type;");
    printf("TODO:");
    int err = sqlite3_exec(db,cmd,printcallback,0,errmsg);
    if (err) {
        fprintf(stderr, "Could not access db: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}

void printdone(sqlite3 *db){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"SELECT Done, Type, Task FROM Tasks ORDER BY Type;");
    printf("TODO:");
    int err = sqlite3_exec(db,cmd,printcallback,0,errmsg);
    if (err) {
        fprintf(stderr, "Could not access db: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}

void printgroup(sqlite3 *db, struct task t){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"SELECT Done, Type, Task FROM Tasks WHERE (Type = '%s' AND Done = 0) OR Task = '%s' ORDER BY Type;",t.group,t.task);
    printf("TODO:");
    int err = sqlite3_exec(db,cmd,printcallback,0,errmsg);
    if (err) {
        fprintf(stderr, "Could not access db: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}

void printgroupdone(sqlite3 *db, struct task t){
    char *cmd = malloc(MAXLINE * sizeof(char));
    char **errmsg = 0;

    sprintf(cmd,"SELECT Done, Type, Task FROM Tasks WHERE Type = '%s' OR Task = '%s' ORDER BY Type;",t.group, t.task);
    printf("TODO:");
    int err = sqlite3_exec(db,cmd,printcallback,0,errmsg);
    if (err) {
        fprintf(stderr, "Could not access db: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    free(cmd);
    return;
}
