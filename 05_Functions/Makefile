CC = gcc
CFLAGS = -fno-stack-protector -no-pie -g
all: 2
2: 2.c
	$(CC) $(CFLAGS) $^ -o 2.out
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o
