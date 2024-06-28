CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra 

1-2: 1-2.c
	$(CC) $(CFLAGS) $^ -o 1-2.out
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o
