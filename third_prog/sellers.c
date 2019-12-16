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
    printf("signal na okonchanie\n");
    flag = 1;
}


int main(int argc, char ** argv){
    signal(SIGTERM, end_work);
    //argv[1] - номер отдела; argv[2] - кол-во посетителей
    int semid, shmid;
    int * turn_p;
    struct sembuf sops;
    key_t key = ftok("./test", atoi(argv[1]));
    /* создание массива семафоров из 1 элемента */
    semid = semget(key, atoi(argv[2]) + 2, 0666 | IPC_CREAT);
    /* создание сегмента разделяемой памяти */
    shmid = shmget(key, atoi(argv[2])*sizeof(int), 0666 | IPC_CREAT);
    turn_p = shmat(shmid, 0, 0);
    sops.sem_flg = 0;
    int i;
    for(i = 1; i < atoi(argv[2])+2; i++){
        semctl(semid, i, SETVAL, (int) 0);
    }
    for (i = 0; i < atoi(argv[2]); ++i)
    {
        turn_p[i] = 0;
    }
    semctl(semid, 0, SETVAL, (int) 1); //0-й семафор для пользования очередью
    printf("otdel %s sozdaet key = %d\n", argv[1], key);
    while(1){
        if (flag == 0){
            //ojidanie pokypatelya
            if (turn_p[0] != 0){
                sops.sem_num = atoi(argv[2]) + 1;
                sops.sem_op = -1;
                semop(semid, &sops, 1);
                //obslyjivay pokypatelya
                sops.sem_num = 0;
                sops.sem_op = -1;
                semop(semid, &sops, 1);
                printf("ya %s obslyjivay sledyshego pod nomerom = %d\n", argv[1], turn_p[0]);
                sops.sem_num = turn_p[0];
                sops.sem_op = 1;
                semop(semid, &sops, 1);
                int j = 0;
                while ((j<atoi(argv[2])) && (turn_p[j] != 0)){
                    turn_p[j] = turn_p[j+1];
                    j++;
                }
                sops.sem_num = 0;
                sops.sem_op = 1;
                semop(semid, &sops, 1);
            }
            sleep(1);
        }
        else{
            break;
        }
    }
    printf("otdel %s okonchil raboty\n", argv[1]);
    /* удаление массива семафоров */
    semctl(semid, 0, IPC_RMID, (int) 0);
  /* удаление сегмента разделяемой памяти */
    shmdt(turn_p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}