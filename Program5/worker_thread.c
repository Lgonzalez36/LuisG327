#include "worker_thread.h"
#include <string.h>
#include "common.h"
#include "request_queue.h"
#include <stdbool.h>

static bool is_prime(int n);
static void process_request(struct request* request, int thread_id);

/*
 * Processes one request.
 */
static void process_request(struct request* request, int thread_id) {
    if (request != NULL) {
        printf("THREAD [%d] processing TASK [%d]\t\n", thread_id, request->number);
        fflush(stdout);
        // Should really do some real work here - so find some primes
        for (int i = 1; i < 10001; ++i) {
            is_prime(i);

        }
        printf("THREAD [%d] Ended TASK[%d]\t\n\n", thread_id, request->number);

    }

#ifdef DEBUG
    printf("thread-%d processed request [%d]\n", thread_id, request->number);
#endif
}

static bool is_prime(int n) {
    if (n == 1) return false;
    bool prime = true;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            prime = false;
            return prime;
        }
    }
    return prime;
}

/*
 * This function continuously runs/loops.
 * if there's a request on the queue, take it off the
 * the queue and call process_request().
 *
 * if no requests are pending then wait on the condition
 * variable until a request arrives.
 *
 * Exit the thread when the request queue is closed.
 */
void* do_work(void* thread_params) {
    while (1) {
        struct worker_thread_params *paramss = (struct worker_thread_params *) thread_params;
        int taskCount = 200;
        pthread_mutex_lock(paramss->req_queue->mutex);
        while (taskCount == 0) {
            pthread_cond_wait(paramss->req_queue->cond_var, paramss->req_queue->mutex);
        }
        taskCount--;
        struct request* get_a_request = get_request(paramss->req_queue);
        pthread_mutex_unlock(paramss->req_queue->mutex);
        process_request(get_a_request, paramss->thread_id);
    }
}
