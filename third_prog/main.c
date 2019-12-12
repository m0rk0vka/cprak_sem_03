#include <stdio.h>
#include "header.h"

int main(int argc, char ** argv){
    int count_sellers = argv[1];
    int count_customers = argv[2];
    int i;
    /*if (fork() == 0){
        execl("./seller", "./seller", (char *) 0);
        _exit(1);
    }*/
    for (i = 0; i < count_customers; i++){
        char * str = "file_";
        char * c = i + '0';
        strcat(str, c);
        FILE *f = fopen(str, "w");
        int j;
        for (j = 0; j < count_sellers; j++){
            int next_in_list = j;
            fputc(next_in_list, f);
        }
        fclose(f);
        /*if (fork() == 0){
            execl("./customer", "./customer", str, (char *) 0);
            _exit(1);
        }*/
    }
    return 0;
}
