.PHONY: clean style
all: server.c udp_client.c tcp_client.c
	gcc -Wall -Werror -Wextra server.c -o server
	gcc -Wall -Werror -Wextra udp_client.c -o udp_client
	gcc -Wall -Werror -Wextra tcp_client.c -o tcp_client
clean:
	rm -rf server tcp_client udp_client
style:
	clang-format -i *.c
