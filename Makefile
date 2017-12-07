.PHONY:clean
CC=gcc
CFLAGS=-Wall

ver=debug

ifeq ($(ver), debug)
CFLAGS += -g -Ddebug
endif

app/school_info:bin/info.o bin/list.o
	$(CC) $(CFLAGS) -o $@ $^

bin/info.o:src/main.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

bin/list.o:src/list.c
	$(CC) $(CFLAGS) -o $@ -Iinclude -c $<

clean:
	-rm bin/info.o bin/list.o app/school_info
