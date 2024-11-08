#include "shmsystemv.h"

int main() {
  key_t key = ftok("server", 0);
  int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
  char *str = (char *)shmat(shmid, NULL, 0);

  sprintf(str, "Hi!");

  printf("Server: Hi!\n");
  while (strcmp(str, "Hi!") == 0) {
    sleep(1);  // Ждем ответа
  }

  printf("Client: %s\n", str);

  shmdt(str);
  shmctl(shmid, IPC_RMID, NULL);
  exit(EXIT_SUCCESS);
}
