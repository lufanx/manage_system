#include "stdinc.h"

#include "server/handle_server_info.h"
#include "common_handle.h"
#include "log.h"

void
send_server_info(int fd, struct socket_info *server_socket_info)
{
	if (server_socket_info == NULL) {
		LOG_ERROR_INFO("Please input argxs\n");
	}

	server_socket_info->pid = getpid();

	if (write(fd, server_socket_info, sizeof(struct socket_info)) < sizeof(struct socket_info)) {
		LOG_ERROR_INFO("Write data error\n");
	}
}

void
input_connect_client_info(int fd)
{
	struct sockaddr_in fdaddr;
	socklen_t len = sizeof(fdaddr);
	char fd_ip[IP_BUFFER];
	int fd_port;

	memset(&fdaddr, 0, sizeof(fdaddr));
	if (getpeername(fd, (struct sockaddr *)&fdaddr, &len) < 0) {
		fprintf(stderr, "Getpeername failed\n");
		return;
	}
	//fd_port = ntohs(fdaddr.sin_port);
	fd_port = GET_PORT(fdaddr.sin_port);
	//inet_ntop(AF_INET, &fdaddr.sin_addr.s_addr, fd_ip, IP_BUFFER);
	GET_IP(AF_INET, &fdaddr.sin_addr.s_addr, fd_ip, IP_BUFFER);

	printf("Current connected client info: IP[%s] PORT[%d] ...\n", fd_ip, fd_port);
}

int
read_client_data(int fd)
{
	char buffer[SOCKET_DATA_BUFFER];
	int size;
	memset(buffer, 0, SOCKET_DATA_BUFFER);

	size = read(fd, buffer, SOCKET_DATA_BUFFER);
	if (size > 0) {
		printf("Client data buffer: %s\n", buffer);
	}

	if (size == 0) {
		printf("Client readly disconnect\n");
		return 1;
	} else if (size < 0) {
		printf("Server read client data failed\n");
		return -1;
	}
	return 0;
	//printf("Client data buffer: %s\n", buffer);
}

void
out_server_info(struct socket_info *server_socket_info)
{
	if (server_socket_info == NULL) {
		LOG_ERROR_INFO("Server socket info is empty\n");
	}
	/*
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		char server_ip[IP_BUFFER];
		int server_port;

		memset(server_ip, 0, IP_BUFFER);

		if (getsockname(sockfd, (struct sockaddr *)&addr, &len) < 0) {
			fprintf(stderr, "getsockname failed\n");
			return;
		}
		server_port = GET_PORT(addr.sin_port);
		//inet_ntop(AF_INET, &addr.sin_addr.s_addr, server_ip, IP_BUFFER);
		GET_IP(AF_INET, &addr.sin_addr.s_addr, server_ip, IP_BUFFER);
	*/
	printf("Server info: IP[%s] PORT[%d] ...\n", server_socket_info->ip, server_socket_info->port);

}
