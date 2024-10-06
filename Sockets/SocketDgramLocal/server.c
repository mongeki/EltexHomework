#include "dgram_local.h"

int main() {
  int sfd;
  struct sockaddr_un saddr, caddr;
  socklen_t len = sizeof(caddr);
  char buf[BUF_SIZE];
  char answer[BUF_SIZE];
  
  unlink(SOCK_PATH);
  
  if ((sfd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sun_family = AF_LOCAL;
  strncpy(saddr.sun_path, SOCK_PATH, sizeof(saddr.sun_path) - 1);

  if (bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
    perror("bind");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  printf("Server is up, waiting...\n");

  while (1) {
    memset(buf, 0, BUF_SIZE);
    memset(answer, 0, BUF_SIZE);
    int bytes_received =
        recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr*)&caddr, &len);
    if (bytes_received <= 0 || strncmp(buf, "exit", 4) == 0) break;
    /*if (buf[bytes_received - 1] == '\n') {
      buf[bytes_received - 1] = '\0';
      --bytes_received;
    }*/
    else buf[bytes_received] = '\0';

    printf("Client: %s\n", buf);
    int answer_len = snprintf(answer, BUF_SIZE, "Принял - \"%s\".", buf);
    sendto(sfd, answer, answer_len, 0, (struct sockaddr*)&caddr, len);
    printf("Server: %s\n", answer);
  }

  close(sfd);
  unlink(SOCK_PATH);

  exit(EXIT_SUCCESS);
}
