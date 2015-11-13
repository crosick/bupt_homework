#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "stdio.h"
#include "stdlib.h"

#define CHECK(x) if(!(x)) { perror(#x " failed"); abort();}

pid_t pid1, pid2;


static void del_handler(int sig)
{
    printf("OUTH\n");
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);
}


static void children_1st_handler(int sig)
{
    printf("Child Process 1 is killed by Parent!\n");
    exit(0);
}

static void children_2nd_handler(int sig)
{
    printf("Child Process 2 is killed by Parent!\n");
    exit(0);
}

int main(void)
{

    pid1 = fork();
    if(pid1 == 0){
        CHECK(setpgid(0, 0) == 0);
        if(signal(SIGUSR1, children_1st_handler) == SIG_ERR){
            exit(-1);
        }
        while( 1 ){
            pause();
        }
    }else if (pid1 == -1){
        exit(1);
    }else{
        pid2 = fork();
        if(pid2 == 0){
            CHECK(setpgid(0, 0) == 0);
            if(signal(SIGUSR1, children_2nd_handler) == SIG_ERR){
                exit(-1);
            }
            while( 1 ){
                sleep(1);
            }
        }else if(pid2==-1){
            exit(-1);
        }else{
            if(signal(SIGINT, del_handler) == SIG_ERR){
                exit(-1);
            }
            waitpid(pid1, NULL, 0);

            waitpid(pid2, NULL, 0);

            printf("Parent Process is killed\n");
        }
    }
}
