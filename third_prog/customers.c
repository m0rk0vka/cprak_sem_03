#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>


int main(int argc, char ** argv){
    //argv[2] - номер покупателя; argv[1] - кол-во покупателей
    int semid, shmid, list_i, i;
    int *turn_p;
    struct sembuf sops;
    //нужен ли массив семафоров на очередь для изменения разделяемой памяти
    for (list_i = 3; list_i < argc; list_i++){
        key_t key = ftok("./test", atoi(argv[list_i]));
        /* создание массива семафоров */
        semid = semget(key, atoi(argv[1]) + 2, 0);
        /* создание сегмента разделяемой памяти */
        shmid = shmget(key, atoi(argv[1])*sizeof(int), 0);
        /*встаём в очередь*/
        turn_p = shmat(shmid, 0, 0);
        sops.sem_flg = 0;
        //printf("list_i = %d, argv[list_i] = %s\n", list_i, argv[list_i]);
        sops.sem_num = 0;
        sops.sem_op = -1;
        semop(semid, &sops, 1);
        i = 0;
        while (turn_p[i] != 0){
            i++;
        }
        turn_p[i] = atoi(argv[2]);
        printf("pokupatel' %d pri (i = %d) vstal v ochered' v %s otdel po key =%d \n", turn_p[i], i, argv[list_i], key);
        sops.sem_num = 0;
        sops.sem_op = 1;
        semop(semid, &sops, 1);
        sops.sem_num = atoi(argv[1])+1;
        sops.sem_op = 1;
        semop(semid, &sops, 1);
        //vyhod iz ocheredi
        sops.sem_num = atoi(argv[2]);
        sops.sem_op = -1;
        semop(semid, &sops, 1);
        shmdt(turn_p);    //отсоединить сегмент разделяемой памяти;
        sleep(1);
    }
    printf("pokupatel' %s vyshel iz magazina\n", argv[2]);
    return 0;
}