#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "header.h"

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char s[])
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


int main(int argc, char ** argv){
    /*int count_sellers = atoi(argv[1]);
    int count_customers = atoi(argv[2]);
    */int i;
    /*if (fork() == 0){
        execl("./seller", "./seller", (char *) 0);
        _exit(1);
    }*/
    char * str = NULL;
    itoa(120, str);
    printf("%s\n", str);
    //for (i = 0; i < count_customers; i++){
        //printf("%s\n", file_name);
        /*FILE *f = fopen(file_name, "w");
        int j;
        for (j = 0; j < count_sellers; j++){
            int next_in_list = j;
            fputc(next_in_list, f);
        }
        fclose(f);*/
        /*if (fork() == 0){
            execl("./customer", "./customer", str, (char *) 0);
            _exit(1);
        }*/
    //}
    return 0;
}
