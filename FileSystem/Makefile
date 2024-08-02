CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
.PHONY: style clean mem
1: 1.c
	$(CC) $(CFLAGS) 1.c -o 1
2: 2.c
	$(CC)  2.c -o 2 -lncursesw -g 
style:
	clang-format -i *.c
clean:
	rm -rf 1 2 output.txt
mem: 2
	valgrind --tool=memcheck --leak-check=yes ./2
