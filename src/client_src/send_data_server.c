#include "stdinc.h"

#include "client/list.h"
#include "client/info_struct.h"
#include "log.h"
#include "client/send_data_server.h"

#define SEND_LIST_SELECT(client_list_select, sockfd)	do {if (write(sockfd,	\
 client_list_select, sizeof(*client_list_select)) <	\
 sizeof(*client_list_select)) {LOG_NOTICE_INFO(	\
"Write list_select error\n");return;}	\
printf("select: %d\n", client_list_select->select);	\
} while (0)

void
send_list_server(struct list_select *client_list_select, int sockfd)
{
	printf("school name = %s\n", client_list_select->pHead->pNext->info.school_name);
	SEND_LIST_SELECT(client_list_select, sockfd);
}
