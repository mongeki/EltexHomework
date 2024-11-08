CC:=gcc
CFLAGS:=-std=c11 -Wall -Werror -Wextra 
SOURCES:=main.c add.c sub.c mul.c div.c
OBJECTS:=$(SOURCES:.c=.o)
.PHONY: all style clean
all: calc
calc: main.c libcalc.a
	$(CC) $(CFLAGS) main.c -o calc -L. -lcalc
libcalc.a: add.o sub.o mul.o div.o
	ar rc libcalc.a $?
add.o: add.c
	$(CC) $(CFLAGS) -c add.c
sub.o: sub.c
	$(CC) $(CFLAGS) -c sub.c
mul.o: mul.c
	$(CC) $(CFLAGS) -c mul.c
div.o: div.c
	$(CC) $(CFLAGS) -c div.c
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o calc
