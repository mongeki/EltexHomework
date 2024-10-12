#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MULTICAST "224.0.0.1"
#define PORT 7777
#define BUF_SIZE 30

int main() {
  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  char buf[BUF_SIZE] = "Hello!";

  if (sock < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr(MULTICAST);

  while (1) {
    if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&addr,
               sizeof(addr)) < 0)
      perror("sendto");
    sleep(2);
  }

  close(sock);
  exit(EXIT_SUCCESS);
}
