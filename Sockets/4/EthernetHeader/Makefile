CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
.PHONY: clean style all
all: 1
1: server.c client.c
	$(CC) $(CFLAGS) server.c -o server
	$(CC) $(CFLAGS) client.c -o client
clean:
	rm -rf a.out 1 2 3 server client
style:
	clang-format -i -style=google *.c
