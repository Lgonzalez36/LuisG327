// parent class

// prog name    file name   
// arg[0]       arg[1]      
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
    printf("\n\n____________________________________________________________\n\n");
    system("ps");
    printf("\n\n____________________________________________________________\n\n");

 	if (argc == 2) {	/* the wrong way */
        printf("\nI HAVE TWO ARGS*********\n");
		if (execl("./execd_pgm", argv[1], argv[1],
			  (char *)0) == -1)
			FATAL("execl \execd_pgm\" 1 failed\n");
	} else if (argc > 2) {	/* the right way */
        printf("\nI HAVE FIVE ARGS*********\n");
		if (execl(argv[1], argv[2], argv[3],
			  argv[4], argv[5], (char *)0) == -1)
			FATAL("execl \"execd_pgm\" 2 failed\n");
	} 
    
	exit(EXIT_SUCCESS);
}
