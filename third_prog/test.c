#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
//#include <conio.h>



void reverse(char * s)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char * s)
{
    int i, sign;

    if ((sign = n) < 0)  /* записываем знак */
        n = -n;          /* делаем n положительным числом */
    i = 0;
    do {       /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';   /* берем следующую цифру */
    } while ((n /= 10) > 0);     /* удаляем */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int main(void){
    int count_sellers = 3;
    int count_customers = 10;
    int i;
    //zapysk magazina
    for(i = 0; i < count_sellers; i++){
        printf("rys'");
        if (fork() == 0){
            char * str;
            char * str_cnt_customers;
            itoa(i+1, str);
            itoa(count_customers, str_cnt_customers);
            printf("%s\n", "rys");
            execlp("./sellers", "./sellers", str, str_cnt_customers, (char *) 0);
            _exit(1);
        }
        wait(0);
    }
    //sozdanie posititelei
    for (i = 0; i < count_customers; i++){
        if (fork() == 0){
            srand(time(NULL));
            int len_list = rand() % count_sellers;
            printf("\n cabzda%d\n", len_list);
            int j;
            char * list[len_list+2];
            itoa(i+1, list[0]);
            itoa(count_customers, list[1]);
            for(j = 2; j < len_list+2; j++){
                int next = rand() / count_sellers;
                itoa(next, list[j]);
            }
            execvp("./customers", list);
            _exit(1);
        }
        wait(0);
    }
}
