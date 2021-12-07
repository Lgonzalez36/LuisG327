#include "request_queue.h"
#include "common.h"
#include <unistd.h>

struct request_queue* create_request_queue(pthread_mutex_t* p_mutex, pthread_cond_t* p_cond_var) {
    struct request_queue* req_queue = malloc(sizeof(struct request_queue));
    if (req_queue ==  NULL) {
        handle_error("Create_request_queue");
    }
    req_queue->mutex = p_mutex;
    req_queue->cond_var = p_cond_var;
    req_queue->is_closed = false;
    req_queue->num_requests = 0;
    req_queue->request_list = NULL;
    req_queue->last_request = NULL;
    req_queue->max_in_queue = 20;
    return req_queue;
}

/* add a request to the requests list */
void add_request(struct request_queue* req_queue, int request_num) {
    int rc = pthread_mutex_lock(req_queue->mutex);
    if (rc) {
        handle_error_en(rc, "muttex lock in add_request line 28\n");
    }
    struct request* a_request = (struct request*)malloc(sizeof(struct request));
    if (!a_request) { /* malloc failed?? */
	    handle_error_en(-500, "add_request: out of memory\n");
    }

    a_request->number = request_num;
    a_request->next = NULL;
    if (request_num == 1) {
        req_queue->request_list = a_request;
        req_queue->last_request = a_request;
        req_queue->num_requests = 1;
    }
    else {
        req_queue->last_request->next = a_request;
        req_queue->last_request = a_request;
        req_queue->num_requests++;
    }
    //printf("\t\tTASK [%d]:\t Added to the queue\n", request_num);
    pthread_cond_signal(req_queue->cond_var);
    pthread_mutex_unlock(req_queue->mutex);
    
}

/*
 * Returns the oldest pending request in the queue.
 * Returns NULL if no requests are pending.
 * The returned request is removed from the queue.
 * The receiver must free the request to release its memory.
 */
struct request* get_request(struct request_queue* req_queue) {
    struct request* get_a_request = (struct request*)malloc(sizeof(struct request));
    do {
        if (req_queue->num_requests == 0) {
            printf("WAITING:\tTASK [%d]\n", get_a_request->number);
            sleep(1);
        }
        if (req_queue->num_requests > 0) {
            get_a_request = req_queue->request_list;
            req_queue->request_list = get_a_request->next;
            if (req_queue->request_list == NULL){
                req_queue->last_request  = NULL;
            }
            req_queue->num_requests--;
            //printf("TASK   [%d]:\t\t\t Removed from the queue\n", get_a_request->number);
            return get_a_request;            
        }
    } while (1);
}

/* returns the number of pending requests in the queue */
int get_pending_request_count(struct request_queue* req_queue) {
    return req_queue->num_requests;
}

/* free any resources used by request queue */
void delete_request_queue(struct request_queue* req_queue) {
    if (req_queue->last_request) 
        free(req_queue->last_request);
    if (req_queue->request_list) 
        free(req_queue->request_list);
    free(req_queue);
}

/* close the queue as it is no longer accepting requests */
void close_request_queue(struct request_queue* req_queue) {
    req_queue->is_closed = true;
}

/* returns true if the request queue is closed */
bool is_request_queue_closed(struct request_queue* req_queue) {
    return req_queue->is_closed;
}