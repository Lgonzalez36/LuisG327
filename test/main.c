#define THREAD 32
#define QUEUE  256

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include "threadpool.h"

int tasks = 0, done = 0;
pthread_mutex_t lock;

void dummy_task(void *arg) {
    usleep(10000);
    pthread_mutex_lock(&lock);
    /* Record the number of successful tasks completed */
    done++;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    threadpool_t *pool;

    /* Initialize mutex */
    pthread_mutex_init(&lock, NULL);

    /* Assertion Thread Pool Creation Successful */
    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    fprintf(stderr, "Pool started with %d threads and "
            "queue size of %d\n", THREAD, QUEUE);

    /* As long as the task queue is not full, add it all the time */
    while(threadpool_add(pool, &dummy_task, NULL, 0) == 0) {
        pthread_mutex_lock(&lock);
        tasks++;
        pthread_mutex_unlock(&lock);
    }

    fprintf(stderr, "Added %d tasks\n", tasks);

    /* Continuously check whether the number of tasks is more than half completed, and if not continue to sleep. */
    while((tasks / 2) > done) {
        usleep(10000);
    }
    /* At this point, destroy the thread pool, 0 for immediate_shutdown */
    assert(threadpool_destroy(pool, 0) == 0);
    fprintf(stderr, "Did %d tasks\n", done);

    return 0;
}