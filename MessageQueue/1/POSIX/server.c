#include <unistd.h>

#include "msgqposix.h"

int main() {
  mqd_t mq;
  struct mq_attr attr;
  char buf[N];

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = N;
  attr.mq_curmsgs = 0;

  mq = mq_open(QNAME, O_CREAT | O_RDWR, 0644, &attr);
  if (mq < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  strcpy(buf, "Hi!");
  if (mq_send(mq, buf, N, 0) < 0) {
    perror("mq_send");
    exit(EXIT_FAILURE);
  }
  printf("Sent to client: %s\n", buf);

  sleep(5);  // time to client, idk why nonblock-mode mq_send

  ssize_t bytes_read = mq_receive(mq, buf, N, NULL);
  if (bytes_read >= 0) {
    buf[bytes_read] = '\0';
    printf("Received from client: %s\n", buf);
  } else {
    perror("mq_receive");
    exit(EXIT_FAILURE);
  }

  mq_close(mq);
  mq_unlink(QNAME);

  exit(EXIT_SUCCESS);
}
