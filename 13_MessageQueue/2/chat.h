#ifndef CHAT_H
#define CHAT_H

#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20
#define MAX_MSG_LEN 100
#define MAX_QNAME_LEN 100
#define MAX_CLIENTS 10
#define HISTORY_SIZE 100

typedef struct {
	char name[MAX_NAME_LEN];
	char message[MAX_MSG_LEN];
} ChatMessage;

typedef struct {
	char name[MAX_NAME_LEN];
	char to_client_qname[MAX_QNAME_LEN];
	char to_server_qname[MAX_QNAME_LEN];
	mqd_t to_client;
	mqd_t to_server;
} Client;

#endif
