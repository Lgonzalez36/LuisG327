/* Example using malloc by TechOnTheNet.com */

/* The size of memory allocated MUST be larger than the data you will put in it */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    /* Define required variables */
    char *ptr;
    size_t length;

    /* Define the amount of memory required */
    length = 50;

    /* Allocate memory for our string */
    ptr = (char *)malloc(length);

    /* Check to see if we were successful */
    if (ptr == NULL)
    {
        /* We were not so display a message */
        printf("Could not allocate required memory\n");

        /* And exit */
        exit(1);
    }

    /* Copy a string into the allocated memory */
    strcpy(ptr, "C malloc at TechOnTheNet.com");

    /* Display the contents of memory */
    printf("%s\n", ptr);

    /* Free the memory we allocated */
    free(ptr);

    return 0;
}