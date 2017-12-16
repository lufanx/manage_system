#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

#include "client/list.h"

void send_data_server(PNODE Phead, int sockfd, int select);
int connect_server(int argc, char *argv[]);

#endif /* __SOCKET_CLIENT_H__  */
