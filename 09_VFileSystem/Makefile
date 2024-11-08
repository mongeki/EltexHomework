CC:=gcc
CFLAGS:=-Wall -Werror -Wextra
.PHONY: style clean mem
1: 1.c
	$(CC) $(CFLAGS) 1.c -o 1
2: 2.c 2_read_directory.c 2_init_wins.c 2_main_loop.c 2_print_list.c
	$(CC) $(CFLAGS) $? -o 2 -lncursesw -g 
style:
	clang-format -i *.c *.h
clean:
	rm -rf 1 2 output.txt
mem: 2
	valgrind --tool=memcheck --leak-check=yes ./2
