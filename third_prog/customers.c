#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>


int main(int argc, char ** argv){
    //argv[2] - номер покупателя; argv[1] - кол-во покупателей
    if (argc <= 10) {
        int semid;
        int shmid;
        int list_i;
        struct sembuf sops;
        sops.sem_num = 0;
        sops.sem_flg = 0;
        int i;
        printf("sozdali pol'zovatelya s argv:\n");
        for (i = 1; i < argc; i++){
            printf("%s ", argv[i]);
        }
        printf("\n");
        //нужен ли массив семафоров на очередь для изменения разделяемой памяти
        for (list_i = 3; list_i < argc; list_i++){
            key_t key = ftok("./test", atoi(argv[list_i]));
            /* создание массива семафоров из одного элемента */
            semid = semget(key, 1, 0);
            /* создание сегмента разделяемой памяти */
            shmid = shmget(key, atoi(argv[1]) * sizeof (int), 0);
            /*встаём в очередь*/
            sops.sem_op = -1;
            semop(semid, &sops, 1);
            printf("pokupatel' %s vstal v ochered' v %s otdel\n", argv[2], argv[list_i]);
            int *turn_p = shmat(key, 0, 0);
            int i = 0;
            while (turn_p[i] != 0){
                i++;
            }
            turn_p[i] = atoi(argv[2]);
            sops.sem_op = 1;
            semop(semid, &sops, 1);
            //printf("pokupatel' %s vstal v ochered' v %s otdel\n", argv[2], argv[list_i]);
            while(turn_p[0] != atoi(argv[2])){
                sleep(1);//kak pravil'no vyiti iz ocheredi
            }
            shmdt(turn_p);    //отсоединить сегмент разделяемой памяти;
            sleep(1);
        }
        printf("pokupatel' %s vyshel iz magazina\n", argv[1]);
        exit(0);
    }
    exit(1);
}