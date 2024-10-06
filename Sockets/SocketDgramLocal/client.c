#include "dgram_local.h"

int main() {
  int sfd;
  struct sockaddr_un saddr;
  char buf[BUF_SIZE];

  if ((sfd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sun_family = AF_LOCAL;
  strncpy(saddr.sun_path, SOCK_PATH, sizeof(saddr.sun_path) - 1);
  if(connect(sfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  while (1) {
    memset(buf, 0, BUF_SIZE);
    printf("Client: ");
    fgets(buf, BUF_SIZE, stdin);
    send(sfd, buf, strlen(buf), 0);
    if (strncmp(buf, "exit", 4) == 0) break;

    int n = recv(sfd, buf, sizeof(buf), 0);
    if (n > 0) buf[n] = '\0';
    printf("Server: %s\n", buf);
  }

  close(sfd);

  exit(EXIT_SUCCESS);
}
