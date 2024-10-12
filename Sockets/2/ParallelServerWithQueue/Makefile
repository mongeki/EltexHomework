.PHONY: clean style
all: server.c client.c
	gcc -Wall -Werror -Wextra server.c -o server -pthread
	gcc -Wall -Werror -Wextra client.c -o client
clean:
	rm -rf server client
style:
	clang-format -i *.c
