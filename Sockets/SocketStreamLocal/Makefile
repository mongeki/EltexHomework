CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
.PHONY: clean style all
all: 1 2 3
1: server.c client.c
	$(CC) $(CFLAGS) server.c -o server
	$(CC) $(CFLAGS) client.c -o client
2: 2.c
	$(CC) $(CFLAGS) 2.c -o 2
3: 3.c
	$(CC) $(CFLAGS) 3.c -o 3
clean:
	rm -rf a.out 1 2 3 server client
style:
	clang-format -i -style=google *.c
