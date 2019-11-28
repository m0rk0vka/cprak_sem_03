#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int fork_1 = 0, fork_2 = 0, fork_3 = 0;
void sighndlr(int s);


int main(int argc, char** argv){
    printf("Ppid = %d\n", getpid());
    signal(SIGTERM, sighndlr);
    if (argc >= 5){
        if((fork_1 = fork()) == 0){
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
                if ((fork_2 = fork()) == 0)
                {
                    dup2(fd[1], 1);
                    close(fd[1]);
                    close(fd[0]);
                    execlp(argv[4], argv[4], (char*)0);
                }
                else if ((fork_3 = fork()) == 0){
                    close(fd[1]);
                    dup2(fd[0], 0);
                    close(fd[0]);
                    execvp(argv[5], argv+5);
                }
                close(fd[1]);
                close(fd[0]);
                wait(0);
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
    if (fork_1 != 0){
        kill(fork_1, s);
        fork_1 = 0;
    }
    if (fork_2 != 0){
        kill(fork_2, s);
        fork_2 = 0;
    }
    if (fork_3 != 0){
        kill(fork_3, s);
        fork_3 = 0;
    }
    exit(0);
}
