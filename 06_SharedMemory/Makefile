CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -g
.PHONY: all clean style
all: 1
1: 1.c
	$(CC) $(CFLAGS) $^ -o 1.out
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o
