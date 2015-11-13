#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(int argc, char* argv[])
{
    pid_t pid1, pid2;
    int error;
    int i = 0;

    pid1 = fork();

    if(pid1 < 0){
        fprintf(stderr, "Fork failed");
    }
    else if (pid1 == 0){
        error = lockf(stdout, F_LOCK, 0);
        if (error == 0)
            printf("%#x: lock succeeds!\n", getpid());
        else
            perror("lockf");
 
    
        lockf(stdout, F_ULOCK, 0);
        
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