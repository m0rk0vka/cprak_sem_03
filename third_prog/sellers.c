#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int flag = 0;

void end_work(int s){
    printf("abc\n");
    flag = 1;
}


int main(int argc, char ** argv){
    signal(SIGTERM, end_work);
    //argv[1] - номер отдела; argv[2] - кол-во посетителей
    int semid;
    int shmid;
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_flg = 0;
    key_t key = ftok("./test", atoi(argv[1]));
    /* создание массива семафоров из 1 элемента */
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
        exit(1);
    /* создание сегмента разделяемой памяти */
    if ((shmid = shmget(key, atoi(argv[2]) * sizeof(int), 0666 | IPC_CREAT)) < 0)
        exit(1);
    printf("creat %s otdel\n", argv[1]);
    int * turn_p = shmat(shmid, 0, 0);
    while(flag == 0){
        if (turn_p[0] == 0){
            printf("smert'\n");
            sleep(1);
        }
        else {
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            printf("ya %s obslyjivay sledyshego\n", argv[1]);
            int j = 0;
            while (turn_p[j] != 0){
                turn_p[j] = turn_p[j+1];
                j++;
            }
            sops.sem_op = 1;
            semop(semid, &sops, 1);
            sleep(1);
        }
    }
    printf("otdel %s okonchil raboty\n", argv[1]);
    /* удаление массива семафоров */
    if (semctl(semid, 0, IPC_RMID, (struct semid_ds *) 0) < 0)
        exit(1);
  /* удаление сегмента разделяемой памяти */
    shmdt(turn_p);
    if (shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0) < 0)
        exit(1);
    exit(0);
}