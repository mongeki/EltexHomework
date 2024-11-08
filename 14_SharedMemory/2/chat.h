#ifndef CHAT_H
#define CHAT_H

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_NAME "/chat_room"
#define SEM_NAME "/chat_semaphore"
#define SEM2_NAME "/chat_semaphore2"

#define MAX_NAME_LEN 20
#define MAX_MSG_LEN 100
#define MAX_QNAME_LEN 100
#define MAX_CLIENTS 10
#define HISTORY_SIZE 100

typedef struct {
	char messages[HISTORY_SIZE][MAX_MSG_LEN];
	int msg_count;
	char clients[MAX_CLIENTS][MAX_NAME_LEN];
	int client_count;
} ChatRoom;

#endif
