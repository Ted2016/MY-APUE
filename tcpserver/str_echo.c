#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAXLINE 100

void str_echo(int sockfd) {
    ssize_t n;
    char buf[MAXLINE];

    for(; ;) {
        while((n = recv(sockfd, buf, MAXLINE, 0)) > 0)
            send(sockfd, buf, n, 0);

        if(n < 0 && errno == EINTR) {
            continue;
        } else {
            if(n < 0)
                fprintf(stderr, "read error");
            break;
        }
    }
}

