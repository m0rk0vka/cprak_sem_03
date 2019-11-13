#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


void sighndlr(int s);


int main(int argc, char** argv){
    signal(SIGTERM, sighndlr);
    if (argc >= 5){
        if(fork() == 0){
            int fd = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0666);
            if (fd == -1){
                perror("");
                return 1;
            }
            dup2(fd, 1);
            close(fd);
            execlp(argv[1], argv[1], argv[2], (char *)0);
        } else{
            int status;
            wait(&status);
            if(WIFEXITED(status) && WEXITSTATUS(status)==0){
                int fd[2];
                pipe(fd);
                if (fork() == 0)
                {
                    dup2(fd[1], 1);
                    execlp(argv[4], argv[4], (char*)0);
                }
                else if (fork() == 0){
                    close(fd[1]);
                    char * str = NULL;
                    scanf("%s", str);
                    printf("%s", str);
                    dup2(fd[0], 0);
                    execvp(argv[5], argv+5);
                }
                wait(0);
                close(fd[1]);
                wait(0);
            }
        }
    } else{
        printf("argc = %d\n", argc);
        printf("Few arguments were given to the command line!\n");
        return 1;
    }
    return 0;
}

void sighndlr(int s){

}
