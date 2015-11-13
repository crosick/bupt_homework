#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid1, pid2;



void main(int argc, char* argv[])
{
    int fd[2];
    char OutPipe[100], InPipe[100];
    pipe(fd);

    pid1 = fork();

    if(pid1 < 0){
        fprintf(stderr, "Fork failed");
    }
    else if (pid1 == 0){
        
        lockf(fd[1],F_LOCK,0);
        sprintf(InPipe, "child 1 process is sending message!");
        write(fd[1], InPipe, 50);
        lockf(fd[1],F_ULOCK,0);
        exit(0);
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
            fprintf(stderr, "Fork failed");        
        }
        else if (pid2 == 0){
            
            lockf(fd[1],F_LOCK,0);
            sprintf(InPipe,"child 2 process is sending message!");
            write(fd[1], InPipe, 50);
            lockf(fd[1],F_ULOCK,0);
            exit(0);

        }
        else{
            wait(0);
            read(fd[0], OutPipe, 50);
            printf("%s\n",OutPipe);
            wait(0);
            read(fd[0], OutPipe, 50);
            printf("%s\n",OutPipe);
            exit(0);
        }
    }
}