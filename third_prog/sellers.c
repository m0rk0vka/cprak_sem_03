#include <stdio.h>
#include "header.h"


/*
void give_prod(void){
    printf("%s\n", "obslyjivay");
    sleep(1);
}
*/


void seller (int semidm, int shmid, int i){
    struct sembuf sops;
    sops.sem_num = i;
    sops.sem_flg = 0;
    while(1){
        sops.sem_op = -1;
        semop(customers, &sops, 1);
        sops.sem_op = 1;
        semop(semid, &semid, 1);
//        give_prod();
    }
}


int main(int argc, char ** argv){
    int semid;
    int shmid;
    //key_t key = frok("./seller", 'a');
    /* создание массива семафоров из одного элемента */
    if ((semid = semget (SEM_ID, 1, PERMS | IPC_CREAT)) < 0)
        exit(1);

    /* создание сегмента разделяемой памяти */
    if ((shmid = shmget (SHM_ID, N_Seller * sizeof (int), PERMS | IPC_CREAT)) < 0)
        exit(1);

    while(1){
        if (semctl(semid, 0, GETVAL, 0))
            continue;

        semctl (semid, 0, SETVAL, 1);


        sleep(1);
    }
    /* удаление массива семафоров */
    if (semctl (semid, 0, IPC_RMID, (struct semid_ds *) 0) < 0)
        exit(1);

  /* удаление сегмента разделяемой памяти */
    //shmdt (msg_p);
    if (shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0) < 0)
        exit(1);

    exit(0);
}