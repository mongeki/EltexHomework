#ifndef QUEUEPS_H
#define QUEUEPS_H

#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <mqueue.h>

#define PORT 7777
#define BUF_SIZE 1024
#define POOL_SIZE 10
#define MSG_FULL "Servers are busy"
#define QNAME "/serverqueue"

#endif
