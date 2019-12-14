#include "func.h"
#include <string.h>

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
