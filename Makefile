.PHONY:clean
CC=gcc
CFLAGS=-Wall

ver=debug

ifeq ($(ver), debug)
CFLAGS += -g -Ddebug
endif
ALL:app/client app/server

app/client:bin/start_client.o bin/list.o bin/socket_client.o
	$(CC) $(CFLAGS) -o $@ $^

bin/start_client.o:app/start_client.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/list.o:src/client_src/list.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/socket_client.o:src/client_src/socket_client.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

app/server:bin/start_server.o bin/handle_server_info.o
	$(CC) $(CFLAGS) -o $@ $^

bin/start_server.o:app/start_server.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/handle_server_info.o:src/server_src/handle_server_info.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

clean:
	-rm bin/start_client.o bin/list.o bin/start_server.o bin/handle_server_info.o \
app/client app/server
	#-rm app/client app/server
