.PHONY:clean
CC=gcc

app/school_info:bin/info.o
	CC -o $@ $<
bin/info.o:src/main.c
	CC -o $@ -Iinclude -c $<

clean:
	-rm bin/info.o app/school_info
