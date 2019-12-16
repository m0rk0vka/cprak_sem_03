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
    fprintf(stdout, "abc\n");
    flag = 1;
}


int main(int argc, char ** argv){
    signal(SIGTERM, end_work);
    //argv[1] - номер отдела; argv[2] - кол-во посетителей
    int semid, shmid;
    int * turn_p;
    struct sembuf sops;
    key_t key = ftok("./test", atoi(argv[1]));
    printf("otdel %s sozdaet key = %d\n", argv[1], key);
    printf("argv[2]=%s\n", argv[2]);
    /* создание массива семафоров из 1 элемента */
    semid = semget(key, atoi(argv[2]) + 2, 0666 | IPC_CREAT);
    /* создание сегмента разделяемой памяти */
    shmid = shmget(key, atoi(argv[2])*sizeof(int), 0666 | IPC_CREAT);
    turn_p = shmat(shmid, 0, 0);
    int i;
    printf("lolllllllll\n");
    for (i = 0; i < atoi(argv[2]); i++){
        printf("pamat': i=%d, turn_p[i]=%d\n", i, turn_p[i]);
        turn_p[i] = 0;
    }
    printf("kaak\n");
    sops.sem_flg = 0;
    semctl(semid, 0, SETVAL, (int) 1); //0-й семафор для пользования очередью
    while(1){
        if (flag == 0){
            sops.sem_num = 1;
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            printf("ya %s obslyjivay sledyshego pod nomerom = %d\n", argv[1], turn_p[0]);
            int j = 0;
            sops.sem_num = 0;
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            sops.sem_num = turn_p[0] + 1;
            while (turn_p[j+1] != 0){
                turn_p[j] = turn_p[j+1];
                j++;
            }
            sops.sem_op = 1;
            semop(semid, &sops, 1);
            sops.sem_num = 0;
            sops.sem_op = 1;
            semop(semid, &sops, 1);
            sleep(1);
        }
        else
            break;
    }
    printf("otdel %s okonchil raboty\n", argv[1]);
    /* удаление массива семафоров */
    semctl(semid, 0, IPC_RMID, (int) 0);
  /* удаление сегмента разделяемой памяти */
    shmdt(turn_p);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}