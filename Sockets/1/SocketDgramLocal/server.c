#include "dgram_local.h"

/* Changed Kerrisk's code */

int main() {
  struct sockaddr_un svaddr, claddr;
  int sfd;
  ssize_t numBytes;
  socklen_t len;
  char buf[BUF_SIZE];

  sfd = socket(AF_LOCAL, SOCK_DGRAM, 0); /* Create server socket */
  if (sfd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  /* Construct well-known address and bind server socket to it */

  memset(&svaddr, 0, sizeof(struct sockaddr_un));
  svaddr.sun_family = AF_UNIX;
  strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path) - 1);

  unlink(SOCK_PATH);

  if (bind(sfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  /* Receive messages, convert to uppercase, and return to client */

  while (1) {
    memset(buf, 0, BUF_SIZE);
    len = sizeof(struct sockaddr_un);
    numBytes =
        recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);
    if (numBytes == -1) {
      perror("recvfrom");
      exit(EXIT_FAILURE);
    }

    printf("Client: %s\n", buf);

    strcat(buf, " - Принял.");

    if (sendto(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, len) < 0) {
      perror("sendto");
      exit(EXIT_FAILURE);
    }
  }
  exit(EXIT_FAILURE);  // Unreachable
}
