#include <stdio.h>
#include "header.h"

/* void get_prod(void){
    sleep (1);
}*/

void customer(int semid, int shmid){
    int i = 0;
    for(i = 0; i < N_Seller; i++){
        struct sembuf sops;
        sops.sem_num = i;
        sops.sem_op = 1;
        sops.sem_flg = 0;
        semop(customers, &sops, 1);
        sops.sem_op = -1;
        semop(semid, &sops, 1);
//        get_prod();
    }
}

int main(int argc, char ** argv){
    if (argc <= N) {
        int semid;
        int shmid;
        //key_t key = frok("./seller", 'a');
        /* создание массива семафоров из одного элемента */
        if ((semid = semget (SEM_ID, 1, 0)) < 0)
            exit(1);

        /* создание сегмента разделяемой памяти */
        if ((shmid = shmget (SHM_ID, N_Seller * sizeof (int), 0)) < 0)
            exit(1);

        /*while(1){
            sleep(1);
        }*/

        //shmdt(msg_p);    //отсоединить сегмент разделяемой памяти;

        exit(0);
    }
    exit(1);
}