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


void *consumer(void *c_no){
    int item, i;
    for(i=0; i<MAXITEMS; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("consumer %d: remove item %d at %d\n", *((int *)c_no), item, out);
        out = (out+1)%BUFFSIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(){
    pthread_t consumer[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFSIZE);
    sem_init(&full, 0, 0);

    int a[2] = {1, 2};

    for(int i=0; i<2; i++){
        pthread_create(&consumer[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i=0; i<2; i++){
        pthread_join(consumer[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}