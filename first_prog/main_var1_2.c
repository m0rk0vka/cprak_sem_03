#include <stdio.h>
#include <ctype.h>
#define ml 80
 
 
int getlen(FILE* in, char* buf, int len, int ch){
    int c, i = 0;
    
    len -= 1;
    while((c = fgetc(in)) != EOF){
        if((i >= len) || (c == ch) || ferror(in))
            break;
        buf[i++] = c;
    }
    buf[i] = '\0';
    return i;
}


void str_rev(char* s, int len){
    for(int  i = 0, j = len - 1; i < j; ++i, --j){
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int main(int argc, char **argv) {
   FILE *input = fopen(argv[0], "r+");
   printf("0\n");
   while(!feof(input)){
      char buf[ml];
      int len = getlen(input, buf, sizeof(buf), '\n');
      str_rev(buf, len);
      printf("%s\n", buf);
      fputs(buf, input);
   }
   fclose(input);
   printf("1\n");
   return 0;
}
