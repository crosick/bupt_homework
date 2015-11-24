#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

void *producer();
void *consumer();

pthread_mutex_t mutex;
sem_t *empty, *full;

const char *empty_name = "Empty!";
const char *full_name = "Full!"; //Die!!


int main(int argc, char const *argv[])
{

    pthread_mutex_init(&mutex, NULL);
    
    // wtf,osx sem_init 不能用
    // sem_init(&empty, 0, 5);
    // sem_init(&full, 0, 0);

    empty = sem_open(empty_name, O_CREAT, 0644, 5);
    full = sem_open(full_name, O_CREAT, 0644, 0);



    pthread_t pro, con;

    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    pthread_mutex_destroy(&mutex);
    
    // sem_destroy(&empty);
    // sem_destroy(&full);

    sem_unlink(empty_name);
    sem_unlink(full_name);


    return 0;
}

void *producer()
{
    buffer_item item;

    while(1) {
        sleep(rand() % 3);
        item = rand();

        sem_wait(empty);
        pthread_mutex_lock(&mutex);
        
        printf("producer produced %d\n", item);
        if (insert_item(item)){
            fprintf(stderr, "report error condition");
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(full);
    }
}

void *consumer()
{
    buffer_item item;


    while(1) {
        sleep(rand() % 3);
        item = rand();

        sem_wait(full);
        pthread_mutex_lock(&mutex);

        
        if (remove_item(&item)){
            fprintf(stderr, "report error condition");
        }else{
            printf("consumer consumed %d\n", item);
        }

        pthread_mutex_unlock(&mutex);
        sem_post(empty);
    }
}