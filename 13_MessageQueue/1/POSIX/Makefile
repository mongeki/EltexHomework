.PHONY: clean style
all: server.c client.c
	gcc server.c -Wall -Werror -Wextra -lrt -o server
	gcc client.c -Wall -Werror -Wextra -lrt -o client
clean:
	rm -rf server client
style:
	clang-format -i --style=google *.c *.h
