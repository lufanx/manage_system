#ifndef __HANDLE_SERVER_INFO_H__
#define __HANDLE_SERVER_INFO_H__

#include "common_handle.h"

//void out_fd(int fd);
void out_server_info(struct socket_info *server_socket_info);
int read_client_data(int fd);
void input_connect_client_info(int fd);
void send_server_info(int fd, struct socket_info *server_socket_info);

#endif /* __SERVER_HANDLE_H__  */
