
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include "../common.h"

int main(int argc, char **argv)
{

	// if (argc > 2 || argc < 7) {
	// 	fprintf(stderr, "Usage: %s {successor_name} [do-it-right]\n",
	// 		argv[0]);
	// 	exit(EXIT_FAILURE);
	// }
    	for (int i=0; i<argc; i++)
		printf("argv[%d]=%s\n", i, argv[i]);

 	if (argc == 2) {	/* the wrong way */
        printf("\nI HAVE TWO ARGS*********\n");
		if (execl("./successor_setnm", argv[1], argv[1],
			  (char *)0) == -1)
			FATAL("execl \"successor_setnm\" 1 failed\n");
	} else if (argc > 2) {	/* the right way */
        printf("\nI HAVE THREE ARGS*********\n");
		if (execl("./successor_setnm", argv[2], argv[1],
			  argv[2], (char *)0) == -1)
			FATAL("execl \"successor_setnm\" 2 failed\n");
	} 
    
	exit(EXIT_SUCCESS);
}

/* vi: ts=8 */