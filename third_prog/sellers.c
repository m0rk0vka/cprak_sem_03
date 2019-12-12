#include <stdio.h>
#include "header.h"


int main(int argc, char ** argv){
    int semid;
    int shmid;
    key_t key = frok("./main", atoi(argv[2]));
    /* создание массива семафоров из 1 элемента */
    if ((semid = semget (key, 1, PERMS | IPC_CREAT)) < 0)
        exit(1);
    /* создание сегмента разделяемой памяти */
    if ((shmid = shmget (key, N_Customers * sizeof (int), PERMS | IPC_CREAT)) < 0)
        exit(1);
    int * turn_p = shmat(shmid, 0, 0);
    while(1){
        if (semctl(semid, 0, GETVAL, 0))
            continue;
        semctl (semid, 0, SETVAL, 1);
        printf("ya # %d obslyjivay\n", atoi(argv[2]));
        sleep(1);
    }
    /* удаление массива семафоров */
    if (semctl (semid, 0, IPC_RMID, (struct semid_ds *) 0) < 0)
        exit(1);
  /* удаление сегмента разделяемой памяти */
    shmdt (turn_p);
    if (shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0) < 0)
        exit(1);
    exit(0);
}