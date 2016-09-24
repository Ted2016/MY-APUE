/* 2016年 09月 24日 星期六 11:42:08 CST */
#include "../apue.h"

static void sig_usr(int);

int 
main(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        fprintf(stderr, "can't catch SIGUSR1");
        exit(1);
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR) {
        fprintf(stderr, "can't catch SIGUSR2");
        exit(1);
    }
    for(;;)
        pause();
}

static void sig_usr(int signo) {
    if(signo == SIGUSR1) 
        printf("received SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        fprintf(stderr, "received signal %d\n", signo);
}


