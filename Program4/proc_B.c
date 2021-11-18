/*
    Luis Gonzalez
    Professor Aloia
    Program 4
    11/17/2021
 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#define SIGUSR1  10
#define SIGINT  2
#define SLP_SEC   3

static volatile sig_atomic_t data_recvd=0;
typedef struct {
	time_t timestamp;
	int signum;
	pid_t sender_pid;
	uid_t sender_uid;
	int data;
} rcv_data_t;
static rcv_data_t recv_data;

static int send_to_A(pid_t target, int sig, int val)
{
	union sigval sv;
	if (kill(target, 0) < 0)
		return -1;

	sv.sival_int = val;
	if (sigqueue(target, sig, sv) == -1)
		return -2;
	return 0;
}


static void read_msg(int signum, siginfo_t *si, void *ctx)
{
	time_t tm;

	if (time(&tm) < 0)
		WARN("time(2) failed\n");

	recv_data.timestamp = tm;
	recv_data.signum = signum;
	recv_data.sender_pid = si->si_pid;
	recv_data.sender_uid = si->si_uid;
	recv_data.data = si->si_value.sival_int;

	data_recvd = 1;
}

static void display_recv_data(void)
{
	char asctm[128];

	ctime_r(&recv_data.timestamp, asctm);
	printf ("\nProducer [%d] received data @ %s"
		" signal #  : %2d\n"
		" Consumer  : PID=%d : UID=%d\n"
		" data item : %d\n",
		getpid(),
		asctm,
		recv_data.signum,
		recv_data.sender_pid,
		recv_data.sender_uid,
		recv_data.data);

    //printf("\n\n THIS IS THE KILL PID: %d\n", recv_data.sender_pid);
    //kill(recv_data.sender_pid, SIGKILL);
}


int main (int argc, char **argv)
{
	int ret=0;
    struct sigaction act;
	act.sa_sigaction = read_msg;
    sigfillset(&act.sa_mask); /* disallow all while handling */
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &act, 0) == -1)
		FATAL("sigaction failure");

	if (argc != 3) {
		fprintf(stderr, "Usage: %s pid-to-send-to value-to-send[int]\n", argv[0]);
        printf("PID of sender: [%d]\n", getpid());
		exit (1);
	}

	// argv[2] needs to be 101010 just bc that how i did my handlers
	while (1){
		if (atoi(argv[2]) != 101010){
			fprintf(stderr, "Usage: %s pid-to-send-to value-to-send[int] has to be 101010\n", argv[0]);
			exit (1);
		}
		if (atoi(argv[2]) == 101010){
			break;
		}

	}
	ret = send_to_A(atol(argv[1]), SIGUSR1, atoi(argv[2]));
	switch (ret) {
		case -1 : FATAL("Target PID invalid or no permission\n");
		case -2 : FATAL("sigqueue failed\n");
		case 0  : printf("Producer [%d]: sent signal %d to PID %ld with data item %d\n", // sig sent to consumer
            getpid(), SIGUSR1, atol(argv[1]), atoi(argv[2]));
            while(1){
                r_sleep(SLP_SEC, 0);
                if (data_recvd) {
                    printf("DATA: %d\n", recv_data.data);
                    if (recv_data.data == 7007){ // 7007 == Producer recived confirmation from consumer 
                        printf("IT WORKS!!!!!!!!!!!!");
                        display_recv_data();
                        ret = 0;
                        ret = send_to_A(recv_data.sender_pid, SIGUSR1, -1); // send a kill sig to recv
                        switch (ret) {
                            case -1 : FATAL("Target PID invalid or no permission\n");
                            case -2 : FATAL("sigqueue failed\n");
                            case 0  : printf("Producer [%d]: sent signal %d to PID %ld with data item %d\n",
                            getpid(), SIGUSR1, atol(argv[1]), -1);
                            data_recvd = 0;
                            printf("\n\nEnter C^Z to stop this process\n");
                            break;
                        }
                    }
                }
            }
	}
	exit (EXIT_SUCCESS);
}