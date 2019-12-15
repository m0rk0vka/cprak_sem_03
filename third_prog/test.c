#include <stdio.h>
#include <stdlib.h>
#include "func.h"


int main(void){
    int count_sellers = 3;
    int count_customers = 3;
    int i;
    char * str_pid = malloc(10);
    itoa(getpid(), str_pid);
    //zapysk magazina
    int signal_arr[count_sellers];
    char * str_cnt_sellers = malloc(5);
    char * str_cnt_customers = malloc(5);
    char * str = malloc(5);
    itoa(count_customers, str_cnt_customers);
    itoa(count_sellers, str_cnt_sellers);
    for(i = 0; i < count_sellers; i++){
        if ((signal_arr[i] = fork()) == 0){
            itoa(i+1, str);
            execlp("./sellers", "./sellers", str, str_cnt_customers, (char *) 0);
        }
    }
    sleep(count_sellers);
    if (fork() == 0){
        execlp("./creat_customers", "./creat_customers",
            str_pid, str_cnt_sellers, str_cnt_customers, (char *) 0);
        _exit(1);
    }
    //wait(0);
    free(str_pid);
    free(str_cnt_customers);
    free(str_cnt_sellers);
    free(str);
    //zakryvaem magazin
    int l;
    for (l = 0; l < count_sellers; l++){
        printf("pid = %d , ", signal_arr[l]);
        printf("kill vernyl = %d \n", kill(signal_arr[l], SIGTERM));
    }
    return 0;
}
