#include "us_xfr.h"

int main() {
  int sock;
  struct sockaddr_un addr;
  char buffer[BUF_SIZE];

  sock = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_LOCAL;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

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
