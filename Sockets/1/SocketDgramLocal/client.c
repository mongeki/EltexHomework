#include "dgram_local.h"

/* Changed Kerrisk's code */
int main() {
  struct sockaddr_un svaddr, claddr;
  int sfd;
  ssize_t numBytes;
  char resp[BUF_SIZE];

  /* Create client socket; bind to unique pathname (based on PID) */

  sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sfd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&claddr, 0, sizeof(struct sockaddr_un));
  claddr.sun_family = AF_UNIX;
  snprintf(claddr.sun_path, sizeof(claddr.sun_path), "/tmp/ud_ucase_cl.%ld",
           (long)getpid());

  if (bind(sfd, (struct sockaddr *)&claddr, sizeof(struct sockaddr_un)) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  /* Construct address of server */

  memset(&svaddr, 0, sizeof(struct sockaddr_un));
  svaddr.sun_family = AF_UNIX;
  strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path) - 1);

  /* Send messages to server; echo responses on stdout */

  while (1) {
    memset(resp, 0, BUF_SIZE);
    char msg[BUF_SIZE];
    printf("Client: ");
    fgets(msg, BUF_SIZE, stdin);  // fgets reads with '\n', ugly output
    if (sendto(sfd, msg, BUF_SIZE, 0, (struct sockaddr *)&svaddr,
               sizeof(struct sockaddr_un)) < 0) {
      perror("sendto");
      exit(EXIT_FAILURE);
    }

    numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
    /* Or equivalently: numBytes = recv(sfd, resp, BUF_SIZE, 0);
                    or: numBytes = read(sfd, resp, BUF_SIZE); */
    if (numBytes == -1) {
      perror("recvfrom");
      exit(EXIT_FAILURE);
    }
    printf("Response: %s\n", resp);
  }

  remove(claddr.sun_path); /* Remove client socket pathname */
  exit(EXIT_SUCCESS);
}
