#include "chat.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
Client clients[MAX_CLIENTS];
int clients_count = 0;        // Shouldn't init here, 1-line-economy
int client_ids[MAX_CLIENTS];  // for thread-safety

ChatMessage history[HISTORY_SIZE];
int history_count = 0;

void broadcast_message(ChatMessage *message) {
  for (int i = 0; i < clients_count; ++i) {
    if (mq_send(clients[i].to_client, (const char *)message,
                sizeof(ChatMessage), 0) < 0) {
      perror("mq_send");
      exit(EXIT_FAILURE);
    }
  }
}

void *client_listener(void *arg) {
  int id = *(int *)arg;  // Client's num in array
  ChatMessage message;
  while (1) {
    if (mq_receive(clients[id].to_server, (char *)&message, sizeof(ChatMessage),
                   NULL) < 0) {
      perror("mq_receive");
      exit(EXIT_FAILURE);
    }
    pthread_mutex_lock(&mutex);
    broadcast_message(&message);
    strcpy(history[history_count].name, message.name);
    strcpy(history[history_count].message, message.message);
    history_count++;
    pthread_mutex_unlock(&mutex);
  }
}
int main() {
  mqd_t server_mqd;  // Queue for registration
  ChatMessage message;
  pthread_t clients_thread[MAX_CLIENTS];  // Processing each client in different
                                          // threads

  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = sizeof(ChatMessage);
  attr.mq_curmsgs = 0;

  mq_unlink("/server_queue");
  server_mqd = mq_open("/server_queue", O_CREAT | O_RDWR, 0666, &attr);
  if (server_mqd < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  while (1) {  // endless loop, 1 iteration - 1 new client
    if (mq_receive(server_mqd, (char *)&message, sizeof(ChatMessage), NULL) <
        0) {
      perror("mq_receive");
      exit(EXIT_FAILURE);
    }
    if (clients_count < MAX_CLIENTS) {
      /* Fill new client's struct */
      strcpy(clients[clients_count].name, message.name);
      sprintf(clients[clients_count].to_client_qname, "/to_client_q_%s",
              message.name);
      sprintf(clients[clients_count].to_server_qname, "/to_server_q_%s",
              message.name);
      clients[clients_count].to_client =
          mq_open(clients[clients_count].to_client_qname, O_RDWR);
      if (clients[clients_count].to_client < 0) {
        perror("mq_open");
        printf("%s", clients[clients_count].to_client_qname);
        exit(EXIT_FAILURE);
      }
      clients[clients_count].to_server =
          mq_open(clients[clients_count].to_server_qname, O_RDWR);
      if (clients[clients_count].to_server < 0) {
        perror("mq_open");
        printf("%s", clients[clients_count].to_server_qname);
        exit(EXIT_FAILURE);
      }

      clients_count++;
      printf("%s has joined!\n", message.name);
      snprintf(message.message, MAX_MSG_LEN, "%s has joined!", message.name);
      broadcast_message(&message);  // Notify everyone about new client
      for (int i = 0; i < history_count;
           ++i) {  // Sending history to new client
        if (mq_send(clients[clients_count - 1].to_client,
                    (const char *)&history[i], sizeof(ChatMessage), 0) < 0) {
          perror("mq_send");
          exit(EXIT_FAILURE);
        }
      }
      client_ids[clients_count - 1] = clients_count - 1;  // thread-safety
      pthread_create(&clients_thread[clients_count - 1], NULL, client_listener,
                     &client_ids[clients_count - 1]);  // thread for each client
    } else
      printf("Server is full\n");
  }
  exit(EXIT_SUCCESS);  // unreachable
}
