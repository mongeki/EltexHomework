#include "queueps.h"

mqd_t queue;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *serving();

int main() {
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

  /* Creating message queue */
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = sizeof(int);
  attr.mq_curmsgs = 0;
  mq_unlink(QNAME);
  queue = mq_open(QNAME, O_CREAT | O_RDWR, 0666, &attr);
  if (queue < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  /* Initializing pool */
  pthread_t server[POOL_SIZE];
  for (int i = 0; i < POOL_SIZE; ++i) {
    pthread_create(&server[i], NULL, serving, NULL);
  }

  printf("Server is up...\n");

  while (1) {
    len = sizeof(claddr);
    int cfd;
    if ((cfd = accept(listener_sock, (struct sockaddr *)&claddr, &len)) < 0) {
      perror("accept");
      continue;
    }
    mq_send(queue, (const char *)&cfd, sizeof(int), 0); // Sending to the queue
  }
  /* pthread_joins, but unreachable */
  close(listener_sock);
  exit(EXIT_SUCCESS);
}

void *serving() {
  while (1) { // Accepting connections loop
    struct sockaddr_in claddr;
    socklen_t len = sizeof(claddr);
    char buf[BUF_SIZE];
    int cfd;

    pthread_mutex_lock(&mutex);
    mq_receive(queue, (char *)&cfd, sizeof(int), NULL);
    pthread_mutex_unlock(&mutex);

    getpeername(cfd, (struct sockaddr *)&claddr, &len); // get endpoint

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
    close(cfd); // Closing
  }
  return NULL;
}
