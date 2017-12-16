#ifndef __SEND_DATA_SERVER_H__
#define __SEND_DATA_SERVER_H__

#include "client/list.h"

void send_list_server(PNODE Phead, int sockfd, int select);

#endif	/* __SEND_DATA_SERVER_H__  */
