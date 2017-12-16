#include "stdinc.h"

#include "client/socket_client.h"
#include "client/list.h"
#include "client/send_data_server.h"
#include "common_handle.h"
#include "log.h"

int sockfd;

void
send_data_server(PNODE Phead, int sockfd, int select)
{
	if (Phead == NULL) {
		LOG_NOTICE_INFO("Phead is empty\n");
		return;
	}

	if (Phead->pNext == NULL) {
		LOG_NOTICE_INFO("List is empty\n");
		return;
	}
	send_list_server(Phead, sockfd, select);
}

static void
write_buf_sockfd(int sockfd)
{
	int size;
	char buf[SOCKET_DATA_BUFFER];
	memset(buf, 0, SOCKET_DATA_BUFFER);

	/* if input is "quit" client connect will close */
	while (NULL != fgets(buf, SOCKET_DATA_BUFFER, stdin)) {
		printf("buf:%s\n", buf);
		if ((size = write(sockfd, buf, SOCKET_DATA_BUFFER)) < SOCKET_DATA_BUFFER) {
			fprintf(stderr, "Client write data failed\n");
			close(sockfd);
			return;
		} else if (!strncmp(buf, "quit", 4)) {
			printf("Client will quit\n");
			close(sockfd);
			break;
		}
		printf("buf:%s\n", buf);
		printf("size: %d\n", size);
	}
}

/*
void
sig_client_handle(int signo)
{
	char quit_buf[] = "quit";
	if (signo == SIGINT) {
		if (write(sockfd, quit_buf, sizeof(quit_buf)) != sizeof(quit_buf)) {
				fprintf(stderr, "Wtite signal failed\n");
				return;
		}
		close(sockfd);
	}
}
*/

static void
read_server_info()
{
	struct socket_info server_socket_info;

	memset(&server_socket_info, 0, sizeof(server_socket_info));

	if (read(sockfd, &server_socket_info, sizeof(server_socket_info)) < 0) {
		LOG_ERROR_INFO("Client read data error\n");
	} else {
		printf("Server IP[%s] PORT[%d] PID[%d]\n", server_socket_info.ip, server_socket_info.port,
		       server_socket_info.pid);
	}
}

int
connect_server(int argc, char *argv[])
{
	//int sockfd;
	struct sockaddr_in clientaddr;
	//int client_port;
	//char client_ip[IP_BUFFER];
	//
	if (argc != 3) {
		LOG_ERROR_INFO("Please input args or argc error\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "Create client sockfd failed\n");
		return -1;
	}
	memset(&clientaddr, 0, sizeof(clientaddr));
	//memset(client_ip, 0, IP_BUFFER);
	clientaddr.sin_family = AF_INET;
	//printf("Please input connect ip: ");
	//scanf("%s", client_ip);
	//printf("Please input connect port: ");
	//scanf("%d", &client_port);
	clientaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &clientaddr.sin_addr.s_addr);

	if (connect(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) < 0) {
		fprintf(stderr, "Client connect failed\n");
		return -1;

	} else {
		printf("Connected to %s:%d...\n", argv[1], atoi(argv[2]));
		read_server_info();
	}

	/*
		if (signal(SIGINT, sig_client_handle) == SIG_ERR) {
			fprintf(stderr, "Sig_client_handle failed\n");
			return;
		}
	*/

	//write_buf_sockfd(sockfd);
	//close(sockfd);
	return sockfd;
}
