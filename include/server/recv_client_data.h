#ifndef __RECV_CLIENT_DATA_H__
#define __RECV_CLIENT_DATA_H__

#include "common_handle.h"

typedef struct queue{
	struct list_select *pBase;
	int front;
	int rear;
}*QUEUE;

int recv_fd(int sockfd);

#endif /* __RECV_CLIENT_DATA_H__  */
