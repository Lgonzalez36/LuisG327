/*

 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#define SIG_COMM  SIGRTMIN
#define SLP_SEC   3
#define SIGUSR1  10

static volatile sig_atomic_t data_recvd=0;
typedef struct {
	time_t timestamp;
	int signum;
	pid_t sender_pid;
	uid_t sender_uid;
	int data;
} rcv_data_t;
static rcv_data_t recv_data;

static int send_to_B(pid_t target, int sig, int val)
{
	union sigval sv;

	if (kill(target, 0) < 0)
		return -1;

	sv.sival_int = val;
	if (sigqueue(target, sig, sv) == -1)
		return -2;
	return 0;
}
/* 
 * read_msg
 * Signal handler for SIG_COMM.
 * The signal's receipt implies a producer has sent us data;
 * read and place the details in the rcv_data_t structure.
 * For reentrant-safety, all signals are masked while this handler runs.
 */
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
	printf ("Consumer [%d] received data @ %s"
		" signal #  : %2d\n"
		" Producer  : PID=%d : UID=%d\n"
		" data item : %d\n",
		getpid(),
		asctm,
		recv_data.signum,
		recv_data.sender_pid,
		recv_data.sender_uid,
		recv_data.data);
}

int main(int argc, char **argv)
{

	struct sigaction act;
	act.sa_sigaction = read_msg;
	sigfillset(&act.sa_mask); /* disallow all while handling */
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &act, 0) == -1)
		FATAL("sigaction failure");

	printf("%s: Hey, consumer here [%d]! Awaiting data from producer\n"
		"(will poll every %ds ...)\n",
		argv[0], getpid(), SLP_SEC);

	/* Poll ... not the best way, but just for this demo... */
	while(1) {
        int ret =0;
        
		r_sleep(SLP_SEC, 0);
		if (data_recvd) {
            if (recv_data.data == 101010){ // 101010 == Comsumer recived data 
                printf("DATA: %d\n", recv_data.data);
                printf("101010!!!!!!!!!!!!\n");
                display_recv_data();
                ret = send_to_B(recv_data.sender_pid, SIGINT, 7007);
                switch (ret) {
                    case -1 : FATAL("Target PID invalid or no permission\n");
                    case -2 : FATAL("sigqueue failed\n");
                    case 0  : printf("\nConsumer [%d]: sent signal %d to PID %ld with data item %d\n\n",
                        getpid(), SIGUSR1, (long)recv_data.sender_pid, 7007);
                        printf("____________________________________________________________________\n");
                        data_recvd = 0;
                }
            }
            if (recv_data.data == -1){ // -1 == Comsumer recived data to terminate it
                printf("DATA: %d\n", recv_data.data);
                printf("-1!!!!!!!!!!!!\n");
                display_recv_data();
                kill(getpid(), SIGKILL);
                exit(EXIT_SUCCESS);
                data_recvd = 0;
                break;
            }
		}
	}

	exit(EXIT_SUCCESS);
}

/* vi: ts=8 */