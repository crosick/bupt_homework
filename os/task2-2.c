#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void print_something(char letter)
{
    int i, error;
    error = lockf(1, F_LOCK, 0);
    if (error == 0)
        printf("%#x: lock succeeds!\n", getpid());
    else
        perror("lockf");   
    
    for(i=0;i<5000;i++){
        printf("%c",letter);
    }

    lockf(1, F_ULOCK, 0);   
}

void main(int argc, char* argv[])
{
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1 < 0){
        fprintf(stderr, "Fork failed");
    }
    else if (pid1 == 0){
        print_something('b');
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
            fprintf(stderr, "Fork failed");        
        }
        else if (pid2 == 0){
            print_something('c');
        }
        else{
            print_something('a');
        }
    }
}