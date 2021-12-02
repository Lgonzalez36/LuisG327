#include "request_queue.h"
#include "../common.h"

struct request_queue* create_request_queue(pthread_mutex_t* p_mutex, pthread_cond_t* p_cond_var) {
    struct request_queue* req_queue = malloc(sizeof(struct request_queue));
    if (req_queue ==  NULL){
        perror("Create_request_queue");
        exit(EXIT_FAILURE);
    }
    req_queue->mutex = p_mutex;
    req_queue->cond_var = p_cond_var;
    req_queue->is_closed = false;
    req_queue->num_requests = 0;
    req_queue->request_list = NULL;
    req_queue->last_request = NULL;
    return req_queue;
}

void add_request(struct request_queue* req_queue, int request_num) {
}

/*
 * Returns the oldest pending request in the queue.
 * Returns NULL if no requests are pending.
 * The returned request is removed from the queue.
 * The receiver must free the request to release its memory.
 */
struct request* get_request(struct request_queue* req_queue) {

    return NULL;
}

int get_pending_request_count(struct request_queue* req_queue) {
    return 0;
}

void delete_request_queue(struct request_queue* req_queue) {
}

void close_request_queue(struct request_queue* req_queue) {
    free(req_queue);
}

bool is_request_queue_closed(struct request_queue* req_queue) {
    return false;
}