#ifndef __SEND_DATA_SERVER_H__
#define __SEND_DATA_SERVER_H__

#include "client/list.h"
#include "common_handle.h"

void send_list_server(struct list_select *client_list_select, int sockfd);

#endif	/* __SEND_DATA_SERVER_H__  */
