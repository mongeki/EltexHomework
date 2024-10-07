#include "msgqsystemv.h"

int main() {
  key_t key = ftok(PATH, 0);
  int msgid = msgget(key, 0666);
  struct msgbuf msg;

  if (msgrcv(msgid, &msg, sizeof(msg.mtext), 0, 0) < 0) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
  }
  printf("Received from server: %s\n", msg.mtext);

  msg.mtype = 2;
  strcpy(msg.mtext, "Hello!");
  if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) < 0) {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
  printf("Sent to server: %s\n", msg.mtext);

  exit(EXIT_SUCCESS);
}
