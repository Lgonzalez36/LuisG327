#include "worker_thread_pool.h"
#include "request_queue.h"
#include <stdlib.h>
#include <assert.h>
#include "common.h"
#include <pthread.h>

static int next_thread_id = 0;
static pthread_t start_worker_thread(struct worker_thread_params* params);


struct worker_thread_pool* create_worker_thread_pool(struct request_queue* req_queue) {
    struct worker_thread_pool* thread_pool = malloc(sizeof(struct worker_thread_pool));
    if (thread_pool ==  NULL){
        perror("Create_worker_thread_pool");
        exit(EXIT_FAILURE);
    }
    thread_pool->req_queue = req_queue;
    thread_pool->thread_list = NULL;
    thread_pool->last_thread = NULL;
    thread_pool->last_thread_id = 0;
    thread_pool->num_threads = 0;
    return thread_pool;
}

/* Adds a new worker thread to thread pool */
void add_worker_thread(struct worker_thread_pool* pool) {
    struct worker_thread_params* params = malloc(sizeof(struct worker_thread_params));
    if (!params)
        handle_error("add_worker_thread:malloc:params");

    struct worker_thread* worker = malloc(sizeof(struct worker_thread));
    if (!worker)
        handle_error("add_worker_thread:malloc:worker");

    struct worker_thread* new_next = pool->thread_list;
    worker->next = new_next;

    // TODO next_thread_id should be in the thread_pool struct
    worker->thread_id = ++next_thread_id;
    worker->thd_params = params;
    worker->total_processed = params->total_processed;

    pool->thread_list = worker;
    pool->num_threads += 1;
    pool->last_thread_id = worker->thread_id;

    params->req_queue = pool->req_queue;
    params->thread_id = worker->thread_id;
    worker->thread = start_worker_thread(params);
}

static pthread_t start_worker_thread(struct worker_thread_params* params){
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread;
    int rval = pthread_create(&thread, &thread_attr, do_work, params);
    if (rval) {
        handle_error_en(rval, "start_worker_thread");
    }
    pthread_attr_destroy(&thread_attr);
    return thread;
}

/* Performs resource clean up and cancel all worker threads. */
void delete_worker_thread_pool(struct worker_thread_pool* pool) {
    while (pool->thread_list != NULL) {
        if (pool->thread_list) {
            free(pool->thread_list->thd_params);
            pool->thread_list = pool->thread_list->next;
        }
    }
    if (pool->last_thread) 
        free(pool->last_thread);
    if (pool->thread_list) 
        free(pool->thread_list);
    free(pool);
}