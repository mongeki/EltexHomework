#include "stream_inet.h"

int main() {
  int sock;
  struct sockaddr_in addr;
  char buffer[BUF_SIZE];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("connect");
    exit(EXIT_FAILURE);
  }

  while (1) {
    printf("Client: ");
    fgets(buffer, BUF_SIZE, stdin);
    send(sock, buffer, strlen(buffer), 0);

    if (strncmp(buffer, "exit", 4) == 0) break;

    memset(buffer, 0, BUF_SIZE);
    recv(sock, buffer, BUF_SIZE, 0);
    printf("Server: %s\n", buffer);
  }

  close(sock);
  exit(EXIT_FAILURE);
}
