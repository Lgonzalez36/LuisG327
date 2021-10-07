#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/param.h>

int main() {
    // char TABSPACE[] = "\t\t";
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);
    printf("_________________________________________________________________________\n\n");
    printf("\n\t\t\tSystem information\n\n");
    printf("_________________________________________________________________________\n");
    printf("Hostname: %s\t\t\t\n", hostname);
    printf("_________________________________________________________________________\n");
    system("cat /proc/cpuinfo | grep -m 1 family");
    system("cat /proc/cpuinfo | grep -m 1 name");
    printf("_________________________________________________________________________\n");
    printf("Kernel version: \n");
    system("cat /proc/version");
    printf("_________________________________________________________________________\n");
    printf("Time since last booted: \n");
    system("tuptime -o u -l");
    printf("_________________________________________________________________________\n");
    printf("CPU time spent in 1/1000 of a second \n");
    printf("%s%s%s%s\n", "      User", "  Nice", " System", " Idle");
    system("cat /proc/stat | grep cpu");
    printf("_________________________________________________________________________\n");
    printf("Amount of memory configured: \n");
    system("grep MemTotal /proc/meminfo");
    printf("_________________________________________________________________________\n");
    printf("Amount of memory avaiable: \n");
    system("grep MemAvailable /proc/meminfo");
    printf("_________________________________________________________________________\n");
    printf("Number of disk I/O request: \n");
    char str[24] = "cat /proc/$$/io";
    system(str);
    printf("_________________________________________________________________________\n");
    printf("Number of context switched: \n");
    system("grep voluntary /proc/$$/status");
    printf("_________________________________________________________________________\n");
    printf("Number of processes since boot: \n");
    system("grep processes /proc/stat");
    printf("_________________________________________________________________________\n\n\n");
}