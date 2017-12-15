#include "stdinc.h"

#include "client/socket_client.h"
#include "common_handle.h"
#include "log.h"

int sockfd;

static void
write_buf_sockfd(int sockfd)
{
	int size;
	char buf[SOCKET_DATA_BUFFER];
	memset(buf, 0, SOCKET_DATA_BUFFER);

	/* if input is "quit" client connect will close */
	//getchar(); /* fgets will read '\n', this will delete '\n' */
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
	struct server_data data;

	memset(&data, 0, sizeof(data));

	if (read(sockfd, &data, sizeof(data)) < 0) {
		LOG_ERROR("Client read data error\n");
	} else {
		printf("Server IP[%s] PORT[%d] PID[%d]\n", data.ip, data.port, data.pid);
	}
}

void
connect_server(int argc, char *argv[])
{
	//int sockfd;
	struct sockaddr_in clientaddr;
	//int client_port;
	//char client_ip[IP_BUFFER];
	//
	if (argc != 3) {
		LOG_ERROR("Please input args or argc error\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "Create client sockfd failed\n");
		return;
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
		return;

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

	write_buf_sockfd(sockfd);
	close(sockfd);
}
