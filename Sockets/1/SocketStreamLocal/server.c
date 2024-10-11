#include "stream_local.h"

int main() {
  int sfd, cfd;
  struct sockaddr_un addr;
  char buf[BUF_SIZE];
  char answer[BUF_SIZE];

  unlink(SV_SOCK_PATH);

  sfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (sfd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_LOCAL;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(sfd, 5) == -1) {
    perror("listen");
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
  unlink(SV_SOCK_PATH);

  exit(EXIT_SUCCESS);
}
