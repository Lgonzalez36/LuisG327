#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include "request_queue.h"
#include "worker_thread_pool.h"
#include "common.h"
#include <assert.h>
#include <unistd.h>

static void nap_random();

int main(int argc, char* argv[]) {
    pthread_mutex_t req_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t req_cond;
    pthread_condattr_t condattr;

    // seed random number to vary results between program executions
    srand(time(0));

    if (pthread_condattr_init(&condattr)){
        handle_error("pthread_condattr_init");
        // perror("pthread_cond_init");
        // exit(EXIT_FAILURE);
    }
    if (pthread_cond_init(&req_cond, &condattr)){
        handle_error("thread_cond");
        // perror("pthread_cond");
        // exit(EXIT_FAILURE);
    }

    pthread_condattr_destroy(&condattr);

    struct request_queue* req_queue = 
        create_request_queue(&req_mutex, &req_cond);

    struct worker_thread_pool* thread_pool =
        create_worker_thread_pool(req_queue);

    printf("Creating workers\n");
    for (int i=0; i < 4; i++){
        printf("IN MAIN: creating THREAD [%d] ...\n", i+1);
        add_worker_thread(thread_pool);
    }

    int number = 1;
    while(number < 201){
        if (number == 200 ) req_queue->is_closed = true;
        add_request(req_queue, number);
        number++;
    }
    
    int i = 0;
    //while ( i < 3 ) {
        //if (thread_pool->thread_list == NULL) break;
        int result_code1 = pthread_join(thread_pool->thread_list->thread, NULL);
        int result_code2 = pthread_join(thread_pool->thread_list->next->thread, NULL);
        int result_code3 = pthread_join(thread_pool->thread_list->next->next->thread, NULL);
        int result_code4 = pthread_join(thread_pool->thread_list->next->next->next->thread, NULL);
        //thread_pool->thread_list->thread = thread_pool->thread_list->next->thread;
        i++;
        assert(!result_code1);
        assert(!result_code2);
        assert(!result_code3);
        assert(!result_code4);
        printf("IN MAIN: Thread %d has ended.\n", i);
    //}
    
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
    sleep_time.tv_nsec = rand() % (1000000000L / 8L);

    // 1,000,000 ns = 1 ms
    fprintf(stderr, "IN MAIN: sleeping for %ld nanoseconds (%ld milliseconds).\n",
            sleep_time.tv_nsec, sleep_time.tv_nsec / 1000000L);

    nanosleep(&sleep_time, NULL);
    exit(EXIT_SUCCESS);
}