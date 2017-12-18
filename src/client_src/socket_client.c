#include "stdinc.h"

#include "client/socket_client.h"
#include "client/list.h"
#include "client/send_data_server.h"
#include "common_handle.h"
#include "log.h"

int sockfd;

void
send_data_server(struct list_select *client_list_select, int sockfd)
{
	if (client_list_select == NULL) {
		LOG_NOTICE_INFO("Phead is empty\n");
		return;
	}

	printf("============\n");
	if (client_list_select->pHead == NULL) {
		LOG_NOTICE_INFO("List is empty\n");
		return;
	}
	//assert(client_list_select->pHead != NULL);
	printf("=============\n");
	send_list_server(client_list_select, sockfd);
}

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
	struct sockaddr_in clientaddr;
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
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &clientaddr.sin_addr.s_addr);

	if (connect(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) < 0) {
		fprintf(stderr, "Client connect failed\n");
		return -1;

	} else {
		printf("Connected to %s:%d...\n", argv[1], atoi(argv[2]));
		read_server_info();
	}

	return sockfd;
}
