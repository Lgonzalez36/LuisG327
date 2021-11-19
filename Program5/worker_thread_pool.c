#include "worker_thread_pool.h"
#include <stdlib.h>
#include <assert.h>

static int next_thread_id = 0;

struct worker_thread_pool* create_worker_thread_pool(
    struct request_queue* req_queue) {
    struct worker_thread_pool thread_pool = malloc(sizeof(struct worker_thread_pool));
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

void add_worker_thread(struct worker_thread_pool* pool) {
    struct worker_thread_params* params = malloc(sizeof(struct worker_thread_params));

    struct worker_thread* woeker = malloc(sizeof(struct worker_thread));
    struct worker_thread* new_next pool->thread_list;
    worker->next = new_next;
    worker->thread_id = ++next_thread_id
    pool->thread_list = worker;
    pool->num_threads += 1;
}

void remove_worker_thread(struct worker_thread_pool* pool) {
}

int get_worker_thread_count(struct worker_thread_pool* pool) {
    return 0;
}

void delete_worker_thread_pool(struct worker_thread_pool* pool) {
}
