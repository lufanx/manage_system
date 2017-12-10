#include "server/handle_server_info.h"
#include "common_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void
read_client_data(int fd)
{
	char buffer[SOCKET_DATA_BUFFER];
	memset(buffer, 0, SOCKET_DATA_BUFFER);
	read(fd, buffer, SOCKET_DATA_BUFFER);
	printf("Client data buffer: %s\n", buffer);
}

void
out_server_info(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	char server_ip[IP_BUFFER];
	int server_port;

	memset(server_ip, 0, IP_BUFFER);

	if (getsockname(sockfd, (struct sockaddr *)&addr, &len) < 0) {
		fprintf(stderr, "getsockname failed\n");
		return;
	}
	server_port = ntohs(addr.sin_port);
	inet_ntop(AF_INET, &addr.sin_addr.s_addr, server_ip, IP_BUFFER);

	printf("Server info: IP[%s] PORT[%d] ...\n", server_ip, server_port);

}
