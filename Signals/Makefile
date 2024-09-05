CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
.PHONY: clean style all
all: 1 2 3
1: 1.c my_kill
	$(CC) $(CFLAGS) 1.c -o 1
2: 2.c
	$(CC) $(CFLAGS) 2.c -o 2
3: 3.c
	$(CC) $(CFLAGS) 3.c -o 3
my_kill: my_kill.c
	$(CC) $(CFLAGS) my_kill.c -o my_kill
clean:
	rm -rf a.out 1 2 3 my_kill
style:
	clang-format -i -style=google *.c
