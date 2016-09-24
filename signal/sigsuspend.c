#include "../apue.h"

//The reason why we use sigsuspend is that we want to block some signals in a safer way

static void sig_int(int);

int main(void) {
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start: ");

    if(signal(SIGINT, sig_int) == SIG_ERR) 
        err_sys("signal(SIGINT) error");
    sigemptyset(&waitmask);
    sigemptyset(&newmask);
    sigaddset(&waitmask, SIGUSR1);
    sigaddset(&newmask, SIGINT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");

    pr_mask("int critical region: ");
    if(sigsuspend(&waitmask) != -1)
        err_sys("sigsuspend error");

    pr_mask("after return from sigsuspend");

    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error: ");

    pr_mask("program exit: ");

    exit(0);
}

static void sig_int (int signo) {
    pr_mask("\nin sig_int: ");
}











