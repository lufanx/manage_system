#include "stdinc.h"

#include "common_handle.h"
#include "log.h"
#include "server/recv_client_data.h"

#define QUEUE_AMOUNT	10

#define QUEUE_INIT(QUEUE_DATA)	do {	\
		QUEUE_DATA = (QUEUE)malloc(sizeof(struct queue));	\
		if (QUEUE_DATA == NULL) {	\
			LOG_ERROR_INFO("QUEUE_DATA malloc failed\n");	\
		}	\
		QUEUE_DATA->pBase = (struct list_select *)malloc(sizeof(struct queue) * QUEUE_AMOUNT);	\
		if (QUEUE_DATA->pBase == NULL) {	\
			LOG_ERROR_INFO("QUEUE_DATA->pBase malloc failed\n");	\
		}	\
		QUEUE_DATA->front = 0;	\
		QUEUE_DATA->rear = 0;	\
	} while (0)

#define QUEUE_FULL(QUEUE_DATA)	do {	\
		if (((QUEUE_DATA->rear+1) % QUEUE_AMOUNT) == QUEUE_DATA->front) {	\
			queue_full_flag = 1;	\
		}	\
		else {	\
			queue_full_flag = 0;	\
		}	\
	} while (0)

#define QUEUE_ADD(QUEUE_DATA, CLIENT_DATA) do {	\
		QUEUE_DATA->pBase = CLIENT_DATA;	\
		queue_currect_flag = QUEUE_DATA->rear;	\
		QUEUE_DATA->rear = (QUEUE_DATA->rear+1) % QUEUE_AMOUNT;	\
	} while (0)

#define QUEUE_TRAVERSE(QUEUE_DATA)	do {	\
		printf("school name: %s\n", QUEUE_DATA->pBase->pHead->info.school_name);	\
	} while (0)


int queue_init_flag = 0;
int queue_full_flag = 0;
int queue_currect_flag = 0;

static void
queue_handle(struct list_select *server_list_select, int queue_init_flag)
{
	QUEUE qe = NULL;
	struct list_select *server;

	server = (struct list_select *)malloc(sizeof(struct list_select));
	if (server == NULL) {
		LOG_ERROR_INFO("Server malloc failed\n");
		return;
	}

	server = server_list_select;
	printf("server: %d\n", server->select);
	printf("***********\n");
	/* QUEUE_INIT only init once  */
	if (queue_init_flag == 1) {
		QUEUE_INIT(qe);
	}
	/* When select = 2, clinet only add list data  */
	if (server->select == 2) {
		printf("*************\n");
		QUEUE_FULL(qe);
		printf("^^^^^^^^^^^^^\n");
		if (queue_full_flag == 1) {
			LOG_NOTICE_INFO("Queue is full\n");
			return;
		} else {
			printf("--------------\n");
			QUEUE_ADD(qe, server_list_select);
			printf("=============\n");
			QUEUE_TRAVERSE(qe);
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
	if (ret == 0) {
		return ret;
	}
	queue_handle(server_list_select, queue_init_flag);

	return ret;
}
