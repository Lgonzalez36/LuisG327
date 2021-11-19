/*
 * ch9/pdfrdr_exec.c
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Hands-on System Programming with Linux"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *
 * From:  Ch 9 : Process Execution
 ****************************************************************
 * Brief Description:
 * A simple demo of using the exec API; this program contains a
 * function to execute a PDF reader application, passing along a
 * PDF file to display.
 *
 * For details, please refer the book, Ch 9.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../common.h"

/* NOTE! We assume that the PDF reader app 'evince' is
 * installed at this location
 */
const char *pdf_reader_app="/usr/bin/evince";

static int exec_pdf_reader_app(char *pdfdoc) {
	char * const pdf_argv[] = {"evince", pdfdoc, 0};

	if (execv(pdf_reader_app, pdf_argv) < 0) {
		WARN("execv failed\n");
		return -1;
	}
	return 0; /* never reached */
}

int main(int argc, char **argv) {  

    pid_t ret;
        system("ps");
        switch ((ret = fork())) {
        case -1:
            FATAL("fork failed, aborting!\n");
            break;
        case 0:
            printf("______________________________________________\n");
            printf("\t\t In child\n\n");
            system("ps");
            if (argc < 2) {
                fprintf(stderr, "Usage: %s {pathname_of_doc.pdf}\n", argv[0]);
                printf("______________________________________________\n");
                exit(EXIT_FAILURE);
            }
            if (exec_pdf_reader_app(argv[1]) < 0)
                FATAL("exec pdf function failed\n");

            exit (EXIT_SUCCESS);
        
        default:
            if (wait(0) < 0) 
                FATAL("wait failed, aborting..\n");
            printf("______________________**________________________\n");
            printf("\t\t In Parent\n\n");
            system("ps");
            printf("______________________***______________________\n");
            break;
        }
}

/* vi: ts=8 */