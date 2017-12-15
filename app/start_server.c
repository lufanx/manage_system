#include "stdinc.h"

#include "server/handle_server_info.h"
#include "log.h"

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
	int ret;
	char buf[1024];

	/* argv[1] is socket port */
	if (argc < 2) {
		LOG_ERROR("usage: %s#port\n", argv[0]);
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
		close(sockfd);
		exit(1);
	}

	if (listen(sockfd, 10) < 0) {
		fprintf(stderr, "Listen failed\n");
		close(sockfd);
		exit(1);
	}

	FD_ZERO(&readfds);
	max_fd = sockfd;
	out_server_info(sockfd);
	while (1) {
		printf("conn_amount: %d\n", conn_amount);
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		timeout.tv_sec = 1000;
		timeout.tv_usec = 5000;
		for (i = 0; i < BACKLOG; i++) {
			if (fd_A[i] != 0) {
				printf("sock: %d\n", fd_A[i]);
				FD_SET(fd_A[i], &readfds);
			}
		}
		if ((fd_num = select(max_fd + 1, &readfds, NULL, NULL, &timeout)) < 0) {
			fprintf(stderr, "Select called failed\n");
			break;
		}
		if (fd_num == 0) {
			printf("Select check timeout...\n");
			continue;
		}
		for (i = 0; i < conn_amount; i++) {
			if (FD_ISSET(fd_A[i], &readfds)) {
				//input_connect_client_info(fd_A[i]);
				ret = recv(fd_A[i], buf, sizeof(buf), 0);
				//ret = read_client_data(fd_A[i]);
				if ((ret < 0) || (!strncmp(buf, "quit", 4)) || (ret == 0)) {
					printf("Close client: %d\n", fd_A[i]);
					close(fd_A[i]);
					FD_CLR(fd_A[i], &readfds);
					fd_A[i] = 0;
					conn_amount--;
				}
				if (ret > 0) {
					printf("fd_A[%d]: buf:%s\n", fd_A[i], buf);
				}
			}
			//out_fd(fd_A[i]);
			//printf("read 1\n");
			//read_client_data(fd_A[i]);
			//printf("read 2\n");

		}
		if (FD_ISSET(sockfd, &readfds)) {
			printf("Server: %d\n", sockfd);
			printf("Server socket waitting accept client......\n");
			fd = accept(sockfd, NULL, NULL);
			send_server_info(fd, argv);
			input_connect_client_info(fd);
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
