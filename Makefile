.PHONY:clean
CC=gcc
CFLAGS=-Wall

ver=debug

ifeq ($(ver), debug)
CFLAGS += -g -Ddebug
endif
ALL:app/client app/server

client_objects = bin/start_client.o bin/list.o bin/socket_client.o bin/log.o bin/send_data_server.o
server_objects = bin/start_server.o bin/handle_server_info.o bin/log.o bin/recv_client_data.o

app/client:$(client_objects)
	$(CC) $(CFLAGS) -o $@ $^

bin/start_client.o:app/start_client.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/list.o:src/client_src/list.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/send_data_server.o:src/client_src/send_data_server.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/socket_client.o:src/client_src/socket_client.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

app/server:$(server_objects)
	$(CC) $(CFLAGS) -o $@ $^

bin/start_server.o:app/start_server.c src/log.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/handle_server_info.o:src/server_src/handle_server_info.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/recv_client_data.o:src/server_src/recv_client_data.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/log.o:src/log.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

clean:
	-rm $(client_objects) $(server_objects) app/client app/server
	#-rm app/client app/server
