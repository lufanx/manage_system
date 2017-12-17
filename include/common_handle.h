#ifndef __COMMON_HANDLE_H__
#define __COMMON_HANDLE_H__

#include "client/list.h"
#include "client/info_struct.h"

#define GET_PORT(port)	ntohs(port)
#define GET_IP(ip_type, addr_ip, fd_ip, ip_buf)	inet_ntop(ip_type, addr_ip, fd_ip, ip_buf)
#define SOCKET_DATA_BUFFER	1024
#define IP_BUFFER	16
#define VA_ARGS_BUF	1024

/* About server process info  */
struct socket_info {
	int sockfd;
	int pid;
	int port;
	char ip[IP_BUFFER];
};

struct list_select {
	PNODE pHead;
	enum list_handle_select select;
};

#endif
