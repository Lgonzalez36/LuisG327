#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include "request_queue.h"
#include "worker_thread_pool.h"

static void nap_random();

int main(int argc, char* argv[]) {
    pthread_mutex_t req_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t req_cond;
    pthread_condattr_t condattr;

    // seed random number to vary results between program executions
    srand(time(0));

    if (pthread_condattr_init(&condattr)){
        // handle_error("pthread_condattr_init");
        perror("pthread_cond_init");
        exit(EXIT_FAILURE);
    }
    if (pthread_cond_init(&req_cond, &condattr)){
        // handle_error("thread_cond");
        perror("pthread_cond");
        exit(EXIT_FAILURE);
    }

    pthread_condattr_destroy(&condattr);

    struct request_queue* req_queue = 
        create_request_queue(&req_mutex, &req_cond);

    struct worker_thread_pool* thread_pool =
        create_worker_thread_pool(req_queue);

    printf("Creating workers\n");
    for (int i=0; i < 4; i++){
        printf("main: creating thread #%d ...\n", i);
        add_worker_thread(thread_pool);
    
    }
    close_request_queue(req_queue);
    delete_worker_thread_pool(thread_pool);
    delete_request_queue(req_queue);

    pthread_exit((void*)0);
    
}

    static void nap_random() {
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    // Generate a value between 0 and 1 second
    // 1,000,000,000 ns = 1000 milliseconds
    sleep_time.tv_nsec = rand() % (1000000000L / 4L);
#ifdef DEBUG
    // 1,000,000 ns = 1 ms
    fprintf(stderr, "main: sleeping for %ld nanoseconds (%ld milliseconds).\n",
            sleep_time.tv_nsec, sleep_time.tv_nsec / 1000000L);
#endif
    nanosleep(&sleep_time, NULL);
    exit(EXIT_SUCCESS);
}
