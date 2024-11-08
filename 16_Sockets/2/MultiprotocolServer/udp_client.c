#include "udp_tcp.h"

int main() {
  int sfd;
  struct sockaddr_in saddr;
  char buf[BUF_SIZE];

  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(PORT);
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (1) {
    printf("Client: ");
    fgets(buf, BUF_SIZE, stdin);
    sendto(sfd, buf, strlen(buf), 0, (struct sockaddr *)&saddr, sizeof(saddr));
    if (strncmp(buf, "exit", 4) == 0)
      break;

    memset(buf, 0, BUF_SIZE);
    int n = recvfrom(sfd, buf, BUF_SIZE, 0, NULL, NULL);
    buf[n] = '\0';
    printf("Server: %s\n", buf);
  }

  close(sfd);

  exit(EXIT_SUCCESS);
}
