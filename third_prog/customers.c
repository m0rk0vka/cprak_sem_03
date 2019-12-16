#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>


int main(int argc, char ** argv){
    //argv[2] - номер покупателя; argv[1] - кол-во покупателей
    if (argc <= 10) {
        int semid, shmid, list_i, i;
        int *turn_p;
        struct sembuf sops;
        //нужен ли массив семафоров на очередь для изменения разделяемой памяти
        for (list_i = 3; list_i < argc; list_i++){
            key_t key = ftok("./test", atoi(argv[list_i]));
            //printf("pokypatel' %s podklychaetsya po key = %d\n", argv[2], key);
            /* создание массива семафоров */
            semid = semget(key, atoi(argv[1]) + 2, 0);
            /* создание сегмента разделяемой памяти */
            shmid = shmget(key, atoi(argv[1]) * sizeof (int), 0);
            /*встаём в очередь*/
            turn_p = shmat(shmid, 0, 0);
            sops.sem_flg = 0;
            sops.sem_num = 0;
            sops.sem_op = -1;
            printf("1\n");
            semop(semid, &sops, 1);
            printf("2\n");
            i = 0;
            while (turn_p[i] != 0){
                i++;
            }
            printf("3\n");
            turn_p[i] = atoi(argv[2]);
            printf("4\n");
            sops.sem_num = 1;
            sops.sem_op = 1;
            printf("5\n");
            semop(semid, &sops, 1);
            printf("6\n");
            sops.sem_num = 0;
            sops.sem_op = 1;
            printf("7\n");
            semop(semid, &sops, 1);
            printf("pokupatel' %s vstal v ochered' v %s otdel\n", argv[2], argv[list_i]);
            //vyhod iz ocheredi
            sops.sem_num = atoi(argv[2]) + 1;
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            shmdt(turn_p);    //отсоединить сегмент разделяемой памяти;
            sops.sem_num = atoi(argv[2]) + 1;
            sops.sem_op = 1;
            semop(semid, &sops, 1);
            sleep(1);
        }
        printf("pokupatel' %s vyshel iz magazina\n", argv[1]);
        exit(0);
    }
    exit(1);
}