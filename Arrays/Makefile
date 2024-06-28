CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra 
all: 1 3 4
1: 1.c
	$(CC) $(CFLAGS) $^ -o 1.out
3: 3.c
	$(CC) $(CFLAGS) $^ -o 3.out
4: 4.c
	$(CC) $(CFLAGS) $^ -o 4.out
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o
