CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -pthread
.PHONY: clean style all
all: 1 2 3
1: 1.c
	$(CC) $(CFLAGS) 1.c -o 1
2: 2.c
	$(CC) $(CFLAGS) 2.c -o 2
3: 3.c 3_customer.c 3_loader.c
	$(CC) $(CFLAGS) $? -o 3
clean:
	rm -rf a.out 1 2 3
style:
	clang-format -i -style=google *.c
