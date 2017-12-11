#include "server/handle_server_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

#define BACKLOG	10
int sockfd;

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
	int max_fd;
	struct timeval timeout;
	fd_set readfds;
	int fd_num;
	int conn_amount = 0;
	int fd_A[BACKLOG] = {0};
	int i;

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
	
	FD_ZERO(&readfds);
	max_fd = sockfd;
	out_server_info(sockfd);
	while (1) {
		printf("conn_amount: %d\n", conn_amount);
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		timeout.tv_sec = 20;
		timeout.tv_usec = 5000;
		for (i = 0; i < BACKLOG; i++) {
			if (fd_A[i] != 0) {
				FD_SET(fd_A[i], &readfds);
			}
		}
		if ((fd_num = select(max_fd+1, &readfds, NULL, NULL, &timeout)) < 0) {
			fprintf(stderr, "Select called failed\n");
			break;
		} 
		if (fd_num == 0) {
			printf("Select check timeout...\n");
			continue;
		}
		printf("=================\n");
		for (i = 0; i < conn_amount; i++) {
			out_fd(fd_A[i]);
			printf("read 1\n");
			read_client_data(fd_A[i]);
			printf("read 2\n");

		}
		if (FD_ISSET(sockfd, &readfds)) {
			printf("Server: %d\n", sockfd);
			printf("Server socket waitting accept client......\n");
			fd = accept(sockfd, NULL, NULL);
			if (conn_amount < BACKLOG) {
				fd_A[conn_amount++] = fd;
				if (fd > max_fd) {
					max_fd = fd;
				}
			}
		}
		
	}

	return 0;
}
