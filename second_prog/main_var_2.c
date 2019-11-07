#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main(int argc, char** argv){
    //if (argc < 4){
    if(fork() == 0){
        int fd = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0666);
        if (fd == -1){
            perror("");
            return 1;
        }
        dup2(fd, 1);
        close(fd);
        execlp(argv[1], argv[1], argv[2], (char *)0);
    }
    else{
        int status;
        wait(&status);
        if(WIFEXITED(status) && WEXITSTATUS(status)==0){
            if(fork() == 0){
                execlp(argv[4], argv[4], (char*)0);
            }
            else{
                int status;
                wait(&status);
                if(WIFEXITED(status) && !WEXITSTATUS(status)){
                    execvp(argv[5], argv+5);
                }
            }
        }
    }
    /*}
    else{
        printf("Few arguments were given to the command line!\n");
        return 1;
    }*/
    return 0;
}
