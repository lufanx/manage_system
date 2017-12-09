#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

static int sockfd;

void
sig_handle(int signo)
{
	if (signo == SIGINT) {
		printf("Server closed: close sockfd\n");
		close(sockfd);
		exit(1);
	}
}

void
out_fd(int fd)
{
	printf("Handle client fd\n");
	return;
}

int
main(int argc, char *argv[])
{
	struct sockaddr_in serveraddr;
	int fd;

	/* argv[1] is socket port */
	if (argc < 2) {
		fprintf(stderr, "usage: %s#port\n", argv[0]);
		exit(1);
	}
	
	/* if use Ctrl + c to close server
 	 * will close sockfd 
 	 * */
	if (signal(SIGINT, sig_handle) == SIG_ERR) {
		fprintf(stderr, "SIGINT handle error\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "Create server sockfd failed\n");
		exit(1);
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *)&serveraddr, 
				sizeof(serveraddr)) < 0) {
		fprintf(stderr, "Bind socket port failed\n");
		exit(1);
	}

	if (listen(sockfd, 10) < 0) {
		fprintf(stderr, "Listen failed\n");
		exit(1);
	}
 
	while (1) {
		printf("Server socket waitting accept client......\n");
		fd = accept(sockfd, NULL, NULL);
		out_fd(fd);
	}

	return 0;
}
