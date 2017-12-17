#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

#include "client/list.h"
#include "common_handle.h"

void send_data_server(struct list_select *client_list_select, int sockfd);
int connect_server(int argc, char *argv[]);

#endif /* __SOCKET_CLIENT_H__  */
