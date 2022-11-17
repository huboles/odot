#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *fp = fopen("/home/huck/.local/state/odot/todo", "w+");

    fclose(fp);
    return 0;
}

