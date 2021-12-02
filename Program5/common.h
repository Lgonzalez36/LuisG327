#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <stdlib.h>

// man pthread_create
#define handle_error_en(en, msg) \
    do {                         \
        errno = en;              \
        perror(msgs);            \
        exit(EXIT_FAILURE);      \
    } while (0)

#define handle_error(msg)        \
    do {                         \
        perror(msgs);            \
        exit(EXIT_FAILURE);      \
    } while (0)

#endif