#ifndef LIB3_H
#define LIB3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_CMDS 128
#define MAX_ARGV 128

void exec_commands(char *input);
#endif
