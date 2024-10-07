#ifndef MSGQSYSTEMV
#define MSGQSYSTEMV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define N 100
#define PATH "server"

struct msgbuf {
  long mtype;
  char mtext[N];
};

#endif
