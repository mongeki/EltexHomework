CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra 
all: 1-2 3 4
1-2: 1-2.c
	$(CC) $(CFLAGS) $^ -o 1-2.out
3: 3.c
	$(CC) $(CFLAGS) $^ -o 3.out
4: 4.c
	$(CC) $(CFLAGS) $^ -o 4.out
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o
