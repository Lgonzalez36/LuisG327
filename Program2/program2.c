#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main() {
    // char TABSPACE[] = "\t\t";
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);
    printf("_________________________________________________________________________\n\n");
    printf("System information\n\n\n\n");
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
    // system("awk '{print int($1/86400)'", "days", "int($1%86400/3600)", ":", "int(($1%3600)/60)" ":", "int($1%60)}' /proc/uptime");
    printf("_________________________________________________________________________\n");
    printf("CPU time spent in \n");
    system("cat /proc/stat | grep cpu");
    printf("_________________________________________________________________________\n");
    printf("Amount of memory configured: \n");
    system("grep MemTotal /proc/meminfo");
    printf("_________________________________________________________________________\n");
    printf("Amount of memory avaiable: \n");
    system("grep MemAvailable /proc/meminfo");
    printf("_________________________________________________________________________\n");
    // have to find out how to find current pid 
    int p_pid = getpid();
    printf("Number of disk I/O request: \n");
    printf("cat /proc/%d/io\n", p_pid);
    printf("_________________________________________________________________________\n");
    printf("Number of context switched: \n");
    system("grep voluntary /proc/$$/status");
    printf("_________________________________________________________________________\n");
    printf("Number of processes since boot: \n");
    system("grep processes /proc/stat");
    printf("_________________________________________________________________________\n\n\n");
}