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
    if (!params) {
        handle_error("add_worker_thread:malloc:params");
        // perror("add_worker_thread:malloc:params");
        // exit(EXIT_FAILURE);
    }
    struct worker_thread* worker = malloc(sizeof(struct worker_thread));
    if (!worker) {
        handle_error("add_worker_thread:malloc:worker");
        // perror("add_worker_thread:malloc:worker");
        // exit(EXIT_FAILURE);    

    }
    struct worker_thread* new_next = pool->thread_list;
    worker->next = new_next;

    // TODO next_thread_id should be in the thread_pool struct
    worker->thread_id = ++next_thread_id;
    pool->thread_list = worker;
    pool->num_threads += 1;
    pool->last_thread_id = worker->thread_id;
    
    params->worker_thd = worker->next;
    
    params->total_processed = 0;
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

/* Removes the first worker thread from the thread pool */
void remove_worker_thread(struct worker_thread_pool* pool) {

}

/* Gets current count of worker threads in thread pool */
int get_worker_thread_count(struct worker_thread_pool* pool) {
    return 0;
}

/* Performs resource clean up and cancel all worker threads. */
void delete_worker_thread_pool(struct worker_thread_pool* pool) {
    free(pool);
}