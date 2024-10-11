#include "simpleps.h"

void *serving(void *arg) {
  /* Is it neccessary to set new port for each thread? */

  int cfd = *((int *)arg);
  free(arg);

  struct sockaddr_in claddr;
  socklen_t len = sizeof(claddr);
  getpeername(cfd, (struct sockaddr *)&claddr, &len); // Get client's endpoint

  char buf[BUF_SIZE];
  while (1) {
    int bytes_received = recv(cfd, buf, sizeof(buf) - 1, 0);
    if (bytes_received <= 0) {
      perror("recv");
      break;
    }
    buf[bytes_received] = '\0';
    for (int i = 0; i < bytes_received; ++i) {
      buf[i] = toupper(buf[i]); // Modify msg
    }
    send(cfd, buf, bytes_received, 0);
  }

  close(cfd);
  return NULL;
}

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

  printf("Server is up...\n");

  while (1) {
    len = sizeof(claddr);
    int *cfd = malloc(sizeof(int)); // thread-safety
    if ((*cfd = accept(listener_sock, (struct sockaddr *)&claddr, &len)) < 0) {
      perror("accept");
      free(cfd);
      continue;
    }
    pthread_t serving_pthread; // Thread for new client
    pthread_create(&serving_pthread, NULL, serving, (void *)cfd);
    pthread_detach(serving_pthread); // To not block
  }

  close(listener_sock); // Unreachable
  exit(EXIT_SUCCESS);
}
