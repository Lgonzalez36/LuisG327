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
    if (pthread_condattr_init(&condattr)) handle_error("pthread_condattr_init");
    if (pthread_cond_init(&req_cond, &condattr)) handle_error("thread_cond");
    pthread_condattr_destroy(&condattr);

    struct request_queue* req_queue = create_request_queue(&req_mutex, &req_cond);
    struct worker_thread_pool* thread_pool = create_worker_thread_pool(req_queue);

    printf("Creating workers\n");
    for (int i=0; i < 4; i++) {
        add_worker_thread(thread_pool);
    }

    int task = 1;
    int reqest_total = 201;
    while(task < (reqest_total)) {
        if (task == (reqest_total -1)) req_queue->is_closed = true;
        add_request(req_queue, task++);
        if (req_queue->num_requests == 0) 
            nap_random();
    }
    
    for (int i = 1; i < 5; i++) {
        if (thread_pool->thread_list == NULL) break;
        int result_code = pthread_join(thread_pool->thread_list->thread, NULL);
        assert(!result_code);
        printf("THREAD [%d] exiting. Processed %d request!\n", i, thread_pool->thread_list->thd_params->total_processed);
        thread_pool->thread_list = thread_pool->thread_list->next;
    }
    
    close_request_queue(req_queue);
    delete_worker_thread_pool(thread_pool);
    delete_request_queue(req_queue);
    pthread_exit((void*)0);
    exit(EXIT_SUCCESS);
}

static void nap_random() {
    printf("NAPPING:\n");
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    // Generate a value between 0 and 1 second
    // 1,000,000,000 ns = 1000 milliseconds
    sleep_time.tv_nsec = rand() % (1000000000L / 6L);

    // 1,000,000 ns = 1 ms
#ifdef DEBUG
    fprintf(stderr, "IN MAIN: sleeping for %ld nanoseconds (%ld milliseconds).\n",
            sleep_time.tv_nsec, sleep_time.tv_nsec / 1000000L);
#endif
    nanosleep(&sleep_time, NULL);
}