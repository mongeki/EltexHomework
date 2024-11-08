#include "msgqsystemv.h"

int main() {
  key_t key = ftok(PATH, 0);

  int msgid = msgget(key, IPC_CREAT | 0666);
  if (msgid < 0) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  struct msgbuf msg;
  msg.mtype = 1;
  strcpy(msg.mtext, "Hi!");

  if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) < 0) {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
  printf("Sent to client: %s\n", msg.mtext);

  if (msgrcv(msgid, &msg, sizeof(msg.mtext), 2, 0) < 0) {
    perror("msgrcv");
    exit(EXIT_FAILURE);
  }
  printf("Received from client - %s\n", msg.mtext);

  msgctl(msgid, IPC_RMID, NULL);
  exit(EXIT_SUCCESS);
}
