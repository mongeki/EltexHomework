CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
.PHONY: clean style all
all: 1 2 3
1: 1.c
	$(CC) $(CFLAGS) 1.c -o 1
2: 2_server.c 2_client.c
	$(CC) $(CFLAGS) 2_server.c -o 2_server
	$(CC) $(CFLAGS) 2_client.c -o 2_client
3: 3_main.c 3_exec.c
	$(CC) $(CFLAGS) 3_main.c 3_exec.c -o 3
clean:
	rm -rf a.out 1 2_server 2_client 3
style:
	clang-format -i -style=google *.c *.h
