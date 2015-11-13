#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char* argv[])
{
    pid_t pid1, pid2;
    int i = 0;

    pid1 = fork();

    if(pid1 < 0){
        fprintf(stderr, "Fork failed");
    }
    else if (pid1 == 0){
        
        for(i=0;i<10000;i++){
            printf("c");
        }
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
            fprintf(stderr, "Fork failed");        
        }
        else if (pid2 == 0){
            for(i=0;i<10000;i++){
                printf("b");
            }
        }
        else{
            for(i=0;i<10000;i++){
                printf("a");
            }
        }
    }
}