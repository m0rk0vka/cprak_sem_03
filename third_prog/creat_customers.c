#include <stdio.h>
#include <stdlib.h>
#include "func.h"


int main(int argc, char ** argv){
    //int pid_test = atoi(argv[1]);
    printf("lol\n");
    int count_customers = atoi(argv[3]);
    int count_sellers = atoi(argv[2]);
    int len_list = rand() % count_sellers;
    int j, k;
    char * list[len_list+3];
    for(j = 0; j < len_list+3; j++){
        list[j] = malloc(5);
    }
    list[0] = "./customers";
    list[1] = argv[3];
    for (k = 0; k < count_customers; k++){
        if (fork() == 0){
            srand(time(NULL));
            itoa(k+1, list[2]);
            for(j = 3; j < len_list+3; j++){
                int next = rand() % count_sellers;
                itoa(next, list[j]);
            }
            printf("sozdanie %s pol'zovatelya\n", list[1]);
            execvp("./customers", list);
            _exit(1);
        }
        //sleep(1);
    }
    //sleep(count_customers);
    int i;
    for (i = 0; i < count_customers; i++){
        wait(0);
        //printf("pokupatel' %d zavershilsya\n", i);
    }
    for (i = 0; i < len_list+3; i++){
        free(list[i]);
    }
    //kill(pid_test, SIGUSR1);
    return 0;
}
