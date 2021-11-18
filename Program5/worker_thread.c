#include "worker_thread.h"
#include "request_queue.h"

/*
 * Processes one request.
 */
static void process_request(struct request* request, int thread_id) {
    if (request) {
        int i;
        printf("Thread '%d' handled request '%d'\n", thread_id,
               request->number);
        fflush(stdout);
        // Should really do some real work here
        for (i = 0; i < 100000; i++)
            ;
    }
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
    return NULL;
}
