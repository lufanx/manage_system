.PHONY:clean
CC=gcc
CFLAGS=-Wall

ver=debug

ifeq ($(ver), debug)
CFLAGS += -g -Ddebug
endif
ALL:app/client app/server

app/client:bin/start_client.o bin/list.o
	$(CC) $(CFLAGS) -o $@ $^

bin/start_client.o:app/start_client.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/list.o:src/client_src/list.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

app/server:bin/start_server.o
	$(CC) $(CFLAGS) -o $@ $<

bin/start_server.o:app/start_server.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	#-rm bin/start_client.o bin/list.o bin/start_server.o app/client app/server
	-rm app/client app/server
