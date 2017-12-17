#include "stdinc.h"

#include "common_handle.h"
#include "log.h"

/*
static void
input_list_select(struct list_select *server_list_select)
{
	server_list_select = (struct list_select *)malloc(sizeof(struct list_select));
	if (server_list_select == NULL) {
		LOG_ERROR_INFO("Malloc failed\n");
		return;
	}

	printf("%s\n", __func__);
	printf("select: %d\n", server_list_select->select);
	printf("===============\n");
}
*/


int
recv_fd(int sockfd)
{
	struct list_select *server_list_select = NULL;
	int ret;

	server_list_select = (struct list_select *)malloc(sizeof(struct list_select));
	if (server_list_select == NULL) {
		LOG_ERROR_INFO("Malloc failed\n");
		return -1;
	}

	ret = recv(sockfd, server_list_select, sizeof(struct list_select), 0);
	printf("select: %d\n", server_list_select->select);
	//input_list_select(server_list_select);

	return ret;
}
