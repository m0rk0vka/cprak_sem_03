#include <stdio.h>
#include "header.h"


int main(int argc, char ** argv){
    if (argc <= N) {
        int semid;
        int shmid;
        key_t key = frok("./main", argv[2]);
        /* создание массива семафоров из одного элемента */
        if ((semid = semget (key, 1, 0)) < 0)
            exit(1);
        /* создание сегмента разделяемой памяти */
        if ((shmid = shmget (key, N_Seller * sizeof (int), 0)) < 0)
            exit(1);
        int *turn_p = shmat(key, 0, 0);
        int i = 0;
        while (turn_p[i] != 0){
            i++;
        }
        turn_p[i] = 1;//нужно чтобы процесс вставания в очередь не совпадал с тем моментом когда из неё кто-то выходит
        while(1){
            sleep(1);
        }
        shmdt(turn_p);    //отсоединить сегмент разделяемой памяти;
        exit(0);
    }
    exit(1);
}