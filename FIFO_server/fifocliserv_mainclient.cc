#include "fifo.h"

int 
main(int argc, char** argv) {
	int readfifo, writefifo;
	size_t len;
	ssize_t n;
	char* ptr, fifoname[MAXLINE], buff[MAXLINE];
	pid_t pid;

	pid =  getpid();
	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
	if(mkfifo(fifoname, FILE_MODE) < 0 && errno != EEXIST)
		err_sys("can't creat %s", fifoname);

	snprintf(buff, sizeof(buff), "%ld", (long)pid);
	len = strlen(buff);
	ptr = buff + len;
	Fgets(ptr, MAXLINE-len, stdin);
	len = strlen(buff);

	writefifo = Open(SERV_FIFO, O_WRONLY, 0);
	Write(writefifo, buff, len);

	readfifo = Open(fifoname, O_RDONLU, 0);
	while((n = Read(readfifo, buff, MAXLINE)) > 0)
		Write(STDOUT_FILENO, buff, n);
	Close(readfifo);
	unlink(fifoname);
	exit(0);
}