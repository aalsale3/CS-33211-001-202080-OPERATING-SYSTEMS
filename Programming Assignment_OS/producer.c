#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXITEMS 2 // maximum number of producable or consumable items
#define BUFFSIZE 2 // the size of the buffer at any instance

sem_t empty, full;
int in = 0; 
int out = 0;

int buffer[BUFFSIZE];
pthread_mutex_t mutex;


void *producer(void *p_no){
    int item, i;
    for(i=0;i<MAXITEMS;i++){
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("producer %d: insert item %d at %d\n", *((int *)p_no), buffer[in], in);
        in = (in+1)%BUFFSIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

int main(){
    pthread_t producer[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFSIZE);
    sem_init(&full, 0, 0);

    int a[2] = {1, 2};

    for(int i=0; i<2; i++){
        pthread_create(&producer[i], NULL, (void *)producer, (void *)&a[i]);
    }

    for(int i=0; i<2; i++){
        pthread_join(producer[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}