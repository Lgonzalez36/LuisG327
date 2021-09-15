#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char some_char;

void* alloc_bytes(size_t num_bytes) {
	void* ptr = NULL;
	ptr = malloc(num_bytes);
	if (!ptr) {
		fprintf(stderr, "malloc(%ld) failed\n", num_bytes);
	}

	return ptr;
}

void *realloc_bytes(void* ptr, size_t num_bytes) {
	void* new_ptr = realloc(ptr, num_bytes);
	if (!new_ptr) {
		fprintf(stderr, "realloc(%ld) failed\n", num_bytes);
	}

	return new_ptr;
}