.PHONY:clean
CC=gcc

app/school_info:bin/info.o bin/list.o
	$(CC) -o $@ $^
bin/info.o:src/main.c
	$(CC) -o $@ -Iinclude -c $<
bin/list.o:src/list.c
	$(CC) -o $@ -Iinclude -c $<

clean:
	-rm bin/info.o bin/list.o app/school_info
