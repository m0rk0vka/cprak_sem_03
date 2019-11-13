#include <stdio.h>

int main(int argc, char ** argv){
    printf("lloolololo");
    char * str = NULL;
    scanf("%s", str);
    printf("%s", str);
    int i;
    for(i = 1; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    return 0;
}