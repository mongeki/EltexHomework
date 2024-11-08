#include "poolps.h"

server pool[MAX_CLIENTS];

void *serving(void *arg);
int get_free_server();

int main() {
  char msg_full[BUF_SIZE] = MSG_FULL;
  int listener_sock;
  struct sockaddr_in svaddr, claddr;
  socklen_t len;

  if ((listener_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  svaddr.sin_family = AF_INET;
  svaddr.sin_addr.s_addr = INADDR_ANY;
  svaddr.sin_port = htons(PORT);

  if (bind(listener_sock, (struct sockaddr *)&svaddr, sizeof(svaddr)) < 0) {
    perror("bind");
    close(listener_sock);
    exit(EXIT_FAILURE);
  }

  if (listen(listener_sock, 10) < 0) {
    perror("listen");
    close(listener_sock);
    exit(EXIT_FAILURE);
  }

  /* Initializing pool */
  for (int i = 0; i < MAX_CLIENTS; ++i) {
    pool[i].id = i;
    pthread_create(&pool[i].ptd, NULL, serving, (void *)&pool[i].id);
    pool[i].port = PORT + i + 1;
    pool[i].is_busy = 0;
  }

  printf("Server is up...\n");

  while (1) {
    char buf[BUF_SIZE];
    len = sizeof(claddr);
    int cfd;
    if ((cfd = accept(listener_sock, (struct sockaddr *)&claddr, &len)) < 0) {
      perror("accept");
      continue;
    }
    int server_id = get_free_server(); // Find free server
    if (server_id < 0) {
      send(cfd, msg_full, strlen(msg_full),
           0); // Send message that pool is busy
    } else {
      printf("New connection, sent to server#%d, port = %d\n", server_id,
             pool[server_id].port);
      sprintf(buf, "%d", pool[server_id].port);
      pool[server_id].is_busy = 1;
      send(cfd, buf, strlen(buf), 0); // Send free server's port
    }
    close(cfd);
  }
  /* pthread_joins, but unreachable */
  close(listener_sock);
  exit(EXIT_SUCCESS);
}

void *serving(void *arg) {
  int myid = *((int *)arg);
  int sock;
  struct sockaddr_in svaddr, claddr;
  socklen_t len;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    pool[myid].is_busy = 1;
    return NULL;
  }

  svaddr.sin_family = AF_INET;
  svaddr.sin_addr.s_addr = INADDR_ANY;
  svaddr.sin_port = htons(pool[myid].port);

  if (bind(sock, (struct sockaddr *)&svaddr, sizeof(svaddr)) < 0) {
    pool[myid].is_busy = 1;
    return NULL;
  }

  listen(sock, 5);

  while (1) { // Accepting connections loop
    char buf[BUF_SIZE];
    len = sizeof(claddr);
    int cfd;

    if ((cfd = accept(sock, (struct sockaddr *)&claddr, &len)) < 0) {
			pool[myid].is_busy = 0;
			continue;
    }

    while (1) { // Processing client loop
      int bytes_received = recv(cfd, buf, sizeof(buf) - 1, 0);
      if (bytes_received <= 0) {
        break;
      }
      buf[bytes_received] = '\0';
      if (strcmp(buf, "exit") == 0) // stop-word
        break;
      for (int i = 0; i < bytes_received; ++i) {
        buf[i] = toupper(buf[i]); // Modify msg
      }
      send(cfd, buf, bytes_received, 0);
    }
    close(cfd);
    pool[myid].is_busy = 0; // Marks itself free
  }

  close(sock); // unreachable
  return NULL;
}

int get_free_server() {
  for (int i = 0; i < MAX_CLIENTS; ++i)
    if (pool[i].is_busy == 0)
      return i;
  return -1;
}
