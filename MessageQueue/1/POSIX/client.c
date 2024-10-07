#include "msgqposix.h"

int main() {
  mqd_t mq;
  char buf[N];

  mq = mq_open(QNAME, O_RDWR);
  if (mq < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  ssize_t bytes_read = mq_receive(mq, buf, N, NULL);
  if (bytes_read >= 0) {
    buf[bytes_read] = '\0';
    printf("Received from server: %s\n", buf);

    strcpy(buf, "123");
    if (mq_send(mq, buf, N, 0) < 0) {
      perror("mq_send");
      exit(EXIT_FAILURE);
    }
    printf("Sent to server: %s\n", buf);
  } else {
    perror("mq_receive");
    exit(EXIT_FAILURE);
  }

  mq_close(mq);

  exit(EXIT_SUCCESS);
}
