#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
//#include <conio.h>



void reverse(char * s)
{
    int i, j;
    char c = '\0';
    for (i = 0, j = strlen(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char * s)
{
    int i = 0;
    do {       /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';   /* берем следующую цифру */
    } while ((n /= 10) > 0);     /* удаляем */
    s[i] = '\0';
    reverse(s);
}


int main(void){
    int count_sellers = 3;
    int count_customers = 3;
    int i;
    //zapysk magazina
    int signal_arr[count_sellers];
    char * str_cnt_customers = malloc(5);
    itoa(count_customers, str_cnt_customers);
    for(i = 0; i < count_sellers; i++){
        if (fork() == 0){
            char * str = malloc(5);
            itoa(i+1, str);
            //printf("tyt' %s\n", str);
            execlp("./sellers", "./sellers", str, str_cnt_customers, (char *) 0);
            //_exit(1);
        }
    }
    //sozdanie posititelei
    sleep(count_sellers);
    int k;
    for (k = 0; k < count_customers; k++){
        if ((signal_arr[k] = fork()) == 0){
            srand(time(NULL));
            int len_list = rand() % count_sellers;
            int j;
            char * list[len_list+3];
            for(j = 0; j < len_list+3; j++){
                list[j] = malloc(5);
            }
            list[0] = "./customers";
            itoa(k+1, list[1]);
            list[2] = str_cnt_customers;
            for(j = 3; j < len_list+3; j++){
                int next = rand() % count_sellers;
                itoa(next, list[j]);
            }
            execvp("./customers", list);
            _exit(1);
        }
        //sleep(1);
    }
    //sleep(count_customers);
    for (i = 0; i < count_customers; i++){
        wait(0);
    }
    int l;
    for (l = 0; l < count_sellers; l++){
        printf("pid = %d\n", signal_arr[l]);
        kill(signal_arr[k], SIGTERM);
    }
    return 0;
}
