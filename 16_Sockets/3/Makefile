.PHONY: clean style
all: broadcast multicast
broadcast: server_broadcast.c client_broadcast.c
	gcc -Wall -Werror -Wextra server_broadcast.c -o server_broadcast
	gcc -Wall -Werror -Wextra client_broadcast.c -o client_broadcast
multicast: server_multicast.c client_multicast.c
	gcc -Wall -Werror -Wextra server_multicast.c -o server_multicast
	gcc -Wall -Werror -Wextra client_multicast.c -o client_multicast
clean:
	rm -rf server_broadcast client_broadcast server_multicast client_multicast
style:
	clang-format -i --style=google *.c
