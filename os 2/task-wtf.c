#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int wait_mark;
pid_t pid1, pid2;

void waiting()
{
    while(wait_mark != 0);
}

void stop()
{
    wait_mark = 0;
}


void main(int argc, char* argv[])
{
    pid1 = fork();

    if(pid1 < 0){
        fprintf(stderr, "Fork failed");
    }
    else if (pid1 == 0){
        wait_mark = 1;
        signal(16,stop);
        sleep(5);
        printf("%d\n", wait_mark);
        lockf(1,F_LOCK,0);
        printf("child process 1 is killed by parent! \n");
        lockf(1,F_ULOCK,0);
        exit(0);
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
            fprintf(stderr, "Fork failed");        
        }
        else if (pid2 == 0){
            wait_mark = 1;
            signal(17,stop);
            sleep(5);
            printf("%d\n", wait_mark);
            lockf(1,F_LOCK,0);
            printf("child process 2 is killed by parent! \n");
            lockf(1,F_ULOCK,0);
            exit(0);

        }
        else{
            wait_mark = 1;
            signal(SIGINT, stop);
            waiting();
            kill(pid1,16);
            kill(pid2,17);
            wait(NULL);
            wait(NULL);
            printf("parent process is killed! \n");
            exit(0);
        }
    }
}