// child class
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include "../common.h"
#include <pthread.h>

int main(int argc, char **argv)
{
	int i;

	if (argc < 1 ) {
		fprintf(stderr, "Usage: %s {successor_name}"
				" [do-it-right-param]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
    system("ps");
    printf("\n\n____________________________________________________________\n");
    printf("List of arguments \n");
	for (i=0; i<argc; i++)
		printf("argv[%d]:\t%s\n", i, argv[i]);

	if (argc > 1 ) {/* the "do-it-right" case! */
        for (i=0; i<argc; i++)
            putenv(argv[i]);

        printf("\nList of variables \n");
        system("printenv PATH");
        system("printenv SHELL");
        system("printenv HOME");
        system("printenv PWD");
        system("printenv EXECD_PGM_NAME");
        system("printenv TEST1");
        system("printenv TEST2");
        system("printenv TEST3");
        

        if (prctl(PR_SET_NAME, getenv("EXECD_PGM_NAME"), 0, 0, 0) < 0)
			FATAL("prctl failed\n");


	} else {         /* wrong way... */
		printf("%s: attempt to implicitly set name to \"%s\""
			" via the argv[0] passed to execl [Wrong]\n",
			argv[0], argv[1]);
	}
    printf("\n\n____________________________________________________________\n");
    system("ps");
    printf("\n____________________________________________________________\n");


	exit (EXIT_SUCCESS);
}
