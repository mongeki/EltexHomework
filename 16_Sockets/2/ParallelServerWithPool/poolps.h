#ifndef POOLPS_H
#define POOLPS_H

#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define PORT 7777
#define BUF_SIZE 1024
#define MAX_CLIENTS 10
#define MSG_FULL "Servers are busy"

typedef struct {
	int id; // for thread-safety only
	pthread_t ptd;
	int port;
	int is_busy;
} server;

#endif
