#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

void *producer(void* pnumber);
void *consumer(void* pnumber);

pthread_mutex_t mutex;
sem_t *empty, *full;

const char *empty_name = "Empty!";
const char *full_name = "Full!"; //Die!!


int main(int argc, char const *argv[])
{
    // wtf,osx sem_init 不能用
    // sem_init(&empty, 0, 5);
    // sem_init(&full, 0, 0);

    int i;
    int sleep_time = atoi(argv[1]);
    int pro_thread_count = atoi(argv[2]);
    int con_thread_count = atoi(argv[3]);

    if ((empty = sem_open(empty_name, O_CREAT, 0644, 5)) == SEM_FAILED) {
        perror("semaphore initilization");
        exit(1);
    }

    if ((full = sem_open(full_name, O_CREAT, 0644, 0)) == SEM_FAILED) {
        perror("semaphore initilization");
        exit(1);
    }

    pthread_t pro, con;
    int *pnumber = malloc(sizeof(int));

    for (i = 0; i < pro_thread_count; ++i)
    {
        *pnumber = i;
        pthread_create(&pro, NULL, producer, (void*)pnumber);
    }

    for (i = 0; i < con_thread_count; ++i)
    {
        *pnumber = i;
        pthread_create(&con, NULL, consumer, (void*)pnumber);
    }
    
    

    // pthread_join(pro, NULL);
    // pthread_join(con, NULL);

    sleep(sleep_time);
    pthread_mutex_destroy(&mutex);
    
    // sem_destroy(&empty);
    // sem_destroy(&full);

    sem_unlink(empty_name);
    sem_unlink(full_name);

    printf("program exit\n");


    return 0;
}

void *producer(void* pnumber)
{
    buffer_item item;
    int number = *((int*)pnumber);

    while(1) {
        sleep(rand() % 3);
        item = rand();

        sem_wait(empty);
        pthread_mutex_lock(&mutex);
        
        printf("producer%d produced %d\n", number, item);
        if (insert_item(item)){
            fprintf(stderr, "report error condition");
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(full);
    }
}

void *consumer(void* pnumber)
{
    buffer_item item;
    int number = *((int*)pnumber);


    while(1) {
        sleep(rand() % 3);
        item = rand();

        sem_wait(full);
        pthread_mutex_lock(&mutex);

        
        if (remove_item(&item)){
            fprintf(stderr, "report error condition");
        }else{
            printf("consumer%d consumed %d\n", number, item);
        }

        pthread_mutex_unlock(&mutex);
        sem_post(empty);
    }
}