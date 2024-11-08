.PHONY: style clean all
all: client.c server.c
	gcc -Wall -Werror -Wextra client.c -o client -lncursesw 
	gcc -Wall -Werror -Wextra server.c -o server
style:
	clang-format -i --style=google *.c
clean:
	rm -rf server client
