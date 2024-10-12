#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 7777
#define BUF_SIZE 30

int main() {
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  char buf[BUF_SIZE];

  if (sock < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr*)&addr, len) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  while (1) {
    if (recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr*)&addr, &len) < 0) {
      perror("recvfrom");
    }
    printf("Broadcast on port %d: %s\n", PORT, buf);
  }

  close(sock);
  exit(EXIT_SUCCESS);
}
