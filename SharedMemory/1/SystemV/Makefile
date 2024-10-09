all: server.c client.c
	gcc -Wall -Werror -Wextra server.c -o server -lrt
	gcc -Wall -Werror -Wextra client.c -o client -lrt
clean:
	rm -rf server client
style:
	clang-format -i --style=google *.c
