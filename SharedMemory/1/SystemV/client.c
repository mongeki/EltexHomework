#include "shmsystemv.h"

int main() {
  key_t key = ftok("server", 0);
  int shmid = shmget(key, SHM_SIZE, 0666);
  char *str = (char *)shmat(shmid, NULL, 0);

  printf("Server: %s\n", str);

  sprintf(str, "Hello!");
  printf("Client: %s\n", str);

  shmdt(str);
  exit(EXIT_SUCCESS);
}
