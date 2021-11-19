#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <request_queue.h>
#include <worker_thread_pool.h>


int main(int argc, char* argv[]) {
    pthread_mutex_t req_mutex = PTHREAD_MUTEX_INITALLIZER;
    pthread_cond_t req_cond;
    pthread_conattr_t condattr;
    
    if (pthread_conattr_init(&condattr)){
        perror("main: ");
        exit(EXIT_FAILURE);
    }
    if (pthread_conattr_init(&req_cond, &condattr)){
        perror("main: ");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
