#include "client/socket_client.h"
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
write_buf_sockfd(int sockfd)
{
	int size;
	char buf[SOCKET_DATA_BUFFER];
	memset(buf, 0, SOCKET_DATA_BUFFER);
	
	/* if input is "quit" client connect will close */
	getchar(); /* fgets will read '\n', this will delete '\n' */
	while (NULL != fgets(buf, SOCKET_DATA_BUFFER, stdin)) {
		if ((size = write(sockfd, buf, SOCKET_DATA_BUFFER)) < SOCKET_DATA_BUFFER) {
			fprintf(stderr, "Client write data failed\n");
			close(sockfd);
			return;
		} else if (!strncmp(buf, "quit", 4)) {
			printf("Client will quit\n");
			close(sockfd);
			break;
		}
		printf("size: %d\n", size);
	}
}

void
connect_server()
{
	int sockfd;
	struct sockaddr_in clientaddr;
	int client_port;
	char client_ip[IP_BUFFER];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "Create client sockfd failed\n");
		return;
	}
	memset(&clientaddr, 0, sizeof(clientaddr));
	memset(client_ip, 0, IP_BUFFER);
	clientaddr.sin_family = AF_INET;
	printf("Please input connect ip: ");
	scanf("%s", client_ip);
	printf("Please input connect port: ");
	scanf("%d", &client_port);
	clientaddr.sin_port = htons(client_port);
	inet_pton(AF_INET, client_ip, &clientaddr.sin_addr.s_addr);
	
	if (connect(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) < 0) {
		fprintf(stderr, "Client connect failed\n");
		return;
	
	}
	write_buf_sockfd(sockfd);
	close(sockfd);
}
