#include "stdinc.h"

#include "common_handle.h"
#include "log.h"
#include "server/recv_client_data.h"

#define QUEUE_AMOUNT	10

#define QUEUE_INIT(QUEUE_DATA)	do {	\
		QUEUE_DATA->pBase = (struct list_select *)malloc(sizeof(struct queue) * QUEUE_AMOUNT);	\
		if (QUEUE_DATA->pBase == NULL) {	\
			LOG_ERROR_INFO("QUEUE_DATA->pBase malloc failed\n");	\
		}	\
		QUEUE_DATA->front = 0;	\
		QUEUE_DATA->rear = 0;	\
	} while (0)

#define QUEUE_FULL(QUEUE_DATA)	do {	\
		if ((QUEUE_DATA->rear+1) % QUEUE_AMOUNT == QUEUE_DATA->front) {	\
			queue_full_flag = 1;	\
		}	\
		else {	\
			queue_full_flag = 0;	\
		}	\
	} while (0)

//#define QUEUE_ADD(QUEUE_DATA, CLIENT_DATA) do {
		
//	}

int queue_init_flag = 0;
int queue_full_flag = 0;

static void
queue_handle(struct list_select *server_list_select, int queue_init_flag)
{
	QUEUE qe = NULL;
	server_list_select = (struct list_select *)malloc(sizeof(struct list_select));
	if (server_list_select == NULL) {
		LOG_ERROR_INFO("Server_list_select malloc failed\n");
		return;
	}

	/* QUEUE_INIT only init once  */
	if (queue_init_flag == 1) {
		QUEUE_INIT(qe);
	}

	/* When select = 2, clinet only add list data  */
	if (server_list_select->select == 2) {
		QUEUE_FULL(qe);
		if (queue_full_flag == 1) {
			LOG_NOTICE_INFO("Queue is full\n");
			return;
		}
	}

	free(server_list_select);	
}

int
recv_fd(int sockfd)
{
	struct list_select *server_list_select = NULL;
	int ret;

	queue_init_flag += 1;
	ret = recv(sockfd, server_list_select, sizeof(struct list_select), 0);
	queue_handle(server_list_select, queue_init_flag);

	return ret;
}
