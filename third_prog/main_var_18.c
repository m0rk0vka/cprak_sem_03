#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

/*переопределение типа семафор */
typedef int semaphore;
/* количество покупателей в магазине*/
int cnt = 0;

/* процесс-продавец*/
void Seller(void){
    while(1){

    }
}

/* процесс-покупатель*/
void Customer(void){
    while(1){

    }
}
int main(int argc, char** argv){
    return 0;
}