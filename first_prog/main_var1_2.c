#include <stdio.h>
#include <string.h>
#define ml 82


int main(int argc, char * argv[]){
    if (argc == 1){
        printf("Command line has not file name!\n");
        return 1;
    }
    if (argc > 2){
        printf("Command line has other arguments!\n");
        return 1;
    }
    if (strlen(argv[1]) > 255){
        printf("File name is too long");
        return 1;
    }
    char str[ml], buf[ml];
    int i, j;
    FILE *file;
    file = fopen(argv[1], "r+");
    while (fgets(str, ml - 1, file) != NULL) {
        int len = strlen(str);
        buf[len] = '\0';
        buf[len-1] = '\n';
        for (i = 0, j = 0; len-2-i >=0 ; i++) {
            if (str[len-1-j] != '\n') {
               buf[i] = str[len-1-j];
               j++;
           }
           else {
                i--;
                j++;
            }
        }
        fseek(file, -len, SEEK_CUR);
        fputs(buf, file);
    }
    fclose(file);
    return 0;
}
