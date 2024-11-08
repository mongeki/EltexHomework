#include "poolps.h"

int main() {
  int lfd, sfd;
  struct sockaddr_in laddr, saddr;
  int port;
  char sport[BUF_SIZE];
  char buffer[BUF_SIZE];

  lfd = socket(AF_INET, SOCK_STREAM, 0); // listener sock
  sfd = socket(AF_INET, SOCK_STREAM, 0); // server sock
  if (lfd == -1) {
    printf("lfd\n");
    perror("socket");
    exit(EXIT_FAILURE);
  }
  if (sfd == -1) {
    printf("lfd\n");
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&laddr, 0, sizeof(laddr));
  memset(&saddr, 0, sizeof(laddr));

  laddr.sin_family = AF_INET;
  laddr.sin_port = htons(PORT);
  laddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  /* Connect to the listener */
  if (connect(lfd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  /* Receive new port */
  recv(lfd, sport, BUF_SIZE, 0);
  sport[bytes] = '\0';
  close(lfd); // Close listener sock
  sscanf(sport, "%d", &port);
  saddr.sin_port = htons(port);

  /* Connect to the server */
  if (connect(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  while (1) {
    printf("Client: ");
    fgets(buffer, BUF_SIZE, stdin);
    send(sfd, buffer, strlen(buffer), 0);

    if (strncmp(buffer, "exit", 4) == 0)
      break;

    memset(buffer, 0, BUF_SIZE);
    recv(sfd, buffer, BUF_SIZE, 0);
    printf("Server: %s\n", buffer);
  }

  close(sfd);
  exit(EXIT_FAILURE);
}
