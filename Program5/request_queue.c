#include "request_queue.h"

struct request_queue* create_request_queue(pthread_mutex_t* p_mutex,
                                           pthread_cond_t* p_cond_var) {
    return NULL;
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
}

bool is_request_queue_closed(struct request_queue* req_queue) {
    return false;
}