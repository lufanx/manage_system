#ifndef __COMMON_HANDLE_H__
#define __COMMON_HANDLE_H__

#define GET_PORT(port)	ntohs(port)
#define GET_IP(ip_type, addr_ip, fd_ip, ip_buf)	inet_ntop(ip_type, addr_ip, fd_ip, ip_buf)
#define SOCKET_DATA_BUFFER	1024
#define IP_BUFFER	16


#endif
