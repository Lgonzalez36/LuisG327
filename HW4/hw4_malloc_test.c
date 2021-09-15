#include <malloc.h>
#include "hw4_malloc.h"

int main() {
	printf("HW4 malloc_stats test driver.\n");

    void* ptr = alloc_bytes(512);
    if (!ptr) {
        fprintf(stderr, "malloc(512) failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("allocated 512 bytes [%p]\n", ptr);
    malloc_stats();

    ptr = realloc_bytes(ptr, 1024);
    if (!ptr) {
        fprintf(stderr, "realloc(1024) failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("allocated 1024 bytes [%p]\n", ptr);
    malloc_stats();

    ptr = realloc_bytes(ptr, 128);
    printf("allocated 128 bytes [%p]\n", ptr);
    malloc_stats();
    

    ptr = realloc_bytes(ptr, 1024*1024);
    printf("allocated 1M bytes [%p]\n", ptr);
    malloc_stats();

    free(ptr);
}