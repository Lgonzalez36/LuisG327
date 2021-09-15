#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern void* alloc_bytes(size_t num_bytes);
extern void* realloc_bytes(void* ptr, size_t num_bytes);
