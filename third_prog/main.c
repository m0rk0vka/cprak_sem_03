#include <stdio.h>
#include "header.h"

int main(int argc, char ** argv){
    int count_sellers = argv[1];
    int count_customers = argv[2];
    int i;
    for (i = 0; i < count_sellers; i++){
        if (fork() == 0){
            execl("./seller", "./seller", (char *) 0);
            _exit(1);
        }
    }
    for (i = 0; i < count_customers; i++){
        if (fork() == 0){
            execl("./customer", "./customer", (char *) 0);
            _exit(1);
        }
    }
    return 0;
}