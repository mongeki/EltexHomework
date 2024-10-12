#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 7777

int main() {
  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  int flag = 1;
  char buf[30] = "Hello!";

  if (sock < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

  while (1) {
    if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&addr,
               sizeof(addr)) < 0)
      perror("sendto");
    sleep(2);
  }

  close(sock);
  exit(EXIT_SUCCESS);
}
