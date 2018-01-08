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
		printf("This is traverse queue...\n");	\
		QUEUE_DATA->pBase->pHead = (PNODE)malloc(sizeof(NODE));	\
		if (QUEUE_DATA->pBase->pHead == NULL) {	\
			LOG_ERROR_INFO("Queue_data->pBase->pHead malloc failed\n");	\
		}	\
		printf("school name: %s\n", QUEUE_DATA->pBase->pHead->info.school_name);	\
		free(QUEUE_DATA->pBase->pHead);	\
	} while (0)


int queue_init_flag = 0;
int queue_full_flag = 0;
int queue_currect_flag = 0;

static void
queue_handle(struct list_select *server_list_select, int queue_init_flag)
{
	QUEUE qe = NULL;

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
		} else {
			QUEUE_ADD(qe, server_list_select);
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

	server_list_select = (struct list_select *)malloc(sizeof(struct list_select));
	if (server_list_select == NULL) {
		LOG_ERROR_INFO("Sever_list_select malloc failed\n");
		exit(EXIT_FAILURE);
	}

	queue_init_flag += 1;
	ret = recv(sockfd, server_list_select, sizeof(struct list_select), 0);
	if (ret == 0) {
		return ret;
	}

	server_list_select->pHead = (PNODE)malloc(sizeof(NODE));
	if (server_list_select->pHead == NULL) {
		LOG_ERROR_INFO("Sever_list_select->pHead malloc failed\n");
	}
	server_list_select->pHead->pNext = (PNODE)malloc(sizeof(NODE));
	if (server_list_select->pHead->pNext == NULL) {
		LOG_ERROR_INFO("Sever_list_select->pHead->pNext malloc failed\n");
	}
	printf("shcool name: %s\n", server_list_select->pHead->pNext->info.school_name);
	queue_handle(server_list_select, queue_init_flag);

	free(server_list_select->pHead->pNext);
	free(server_list_select->pHead);

	free(server_list_select);

	return ret;
}
