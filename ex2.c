//
// Created by lukile on 04/06/19.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//Execute a program launch one thread and compute time.
//After 5 seconds signal is sent to main thread and display "count is done"
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *timer (void *arg) {
        sleep(5);
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
}


int main(int argc, char** argv) {
    pthread_t thread;

    if(pthread_create(&thread, NULL, timer, NULL) != 0) {
        exit(EXIT_FAILURE);
    }


    pthread_cond_wait(&cond, &mutex);
    fprintf(stderr, "Count is done\n");

        return EXIT_SUCCESS;
    }
