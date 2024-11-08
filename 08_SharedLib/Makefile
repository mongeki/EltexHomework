CC:=gcc
CFLAGS:=-std=c11 -Wall -Werror -Wextra 
SOURCES:=main.c add.c sub.c mul.c div.c
OBJECTS:=$(SOURCES:.c=.o)
.PHONY: all style clean
all: calc
	LD_LIBRARY_PATH=$(PWD):$(LIBRARY_PATH) ./calc
calc: main.c libcalc.so
	$(CC) $(CFLAGS) main.c -o calc -L. -lcalc
libcalc.so: add.o sub.o mul.o div.o
	$(CC) $(CFLAGS) -shared $? -o libcalc.so
add.o: add.c
	$(CC) $(CFLAGS) -c -fPIC add.c
sub.o: sub.c
	$(CC) $(CFLAGS) -c -fPIC sub.c
mul.o: mul.c
	$(CC) $(CFLAGS) -c -fPIC mul.c
div.o: div.c
	$(CC) $(CFLAGS) -c -fPIC div.c
style:
	clang-format --style=google -i *.c
clean:
	rm -rf *.out *.o *.so calc
