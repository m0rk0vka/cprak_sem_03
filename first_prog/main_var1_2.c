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
        printf("File name is too long!\n");
        return 1;
    }
    FILE *file;
    file = fopen(argv[1], "r+");
    if (file == NULL){
        printf("No such file!\n");
        return 1;
    }
    char str[ml], buf[ml];
    int i;
    while (fgets(str, ml - 1, file) != NULL) {
        int len = strlen(str);
        buf[len] = '\0';
        if (str[len-1] == '\n')
        {
            buf[len-1] = '\n';
            for(i=0; i<=len-2; i++)
            {
                buf[i] = str[len-2-i];
            }
        }
        else
        {
            for (i = 0; i<=len-1; i++)
            {
                    buf[i] = str[len-1-i];
            }
        }
        fseek(file, -len, SEEK_CUR);
        fputs(buf, file);
    }
    fclose(file);
    return 0;
}
