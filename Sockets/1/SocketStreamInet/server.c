#include "stream_inet.h"

int main() {
  int sfd, cfd;
  struct sockaddr_in addr;
  char buf[BUF_SIZE];
  char answer[BUF_SIZE];

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);

  if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  if (listen(sfd, 5) == -1) {
    perror("listen");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  printf("Server is up, waiting...\n");

  cfd = accept(sfd, NULL, NULL);
  if (cfd == -1) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  while (1) {
    memset(buf, 0, BUF_SIZE);
    memset(answer, 0, BUF_SIZE);
    int bytes_received = recv(cfd, buf, BUF_SIZE, 0);
    if (bytes_received <= 0) break;
    if (buf[bytes_received - 1] ==
        '\n') {  // In my case, buf received with \n, need to delete
      buf[bytes_received - 1] = '\0';
      --bytes_received;
    }
    if (strncmp(buf, "exit", 4) == 0) break;

    printf("Client: %s\n", buf);
    int answer_len = snprintf(answer, BUF_SIZE, "Принял - \"%s\".", buf);
    send(cfd, answer, answer_len, 0);
    printf("Server: %s\n", answer);
  }

  close(cfd);
  close(sfd);

  exit(EXIT_SUCCESS);
}
