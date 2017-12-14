#ifndef __HANDLE_SERVER_INFO_H__
#define __HANDLE_SERVER_INFO_H__

//void out_fd(int fd);
void out_server_info(int sockfd);
int read_client_data(int fd);
void input_connect_client_info(int fd);

#endif /* __SERVER_HANDLE_H__  */
