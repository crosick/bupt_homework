#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char* argv[])
{
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1 < 0){
        fprintf(stderr, "Fork failed");
    }
    else if (pid1 == 0){
        printf("b");
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
            fprintf(stderr, "Fork failed");        
        }
        else if (pid2 == 0){
            printf("c");
        }
        else{
            printf("a");
        }
    }
}