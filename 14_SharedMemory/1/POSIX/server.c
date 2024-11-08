#include "shmposix.h"

int main() {
  // Creating
  int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

  // Setting length
  ftruncate(shm_fd, MSG_SIZE);

  // Saving pointer
  char *ptr = mmap(0, MSG_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

  // Writing message
  sprintf(ptr, "Hi!");

  printf("Server: Hi!\n");

  while (strcmp(ptr, "Hi!") == 0) {  // Waiting for response
    sleep(1);
  }

  printf("Client: %s\n", ptr);

  munmap(ptr, MSG_SIZE);
  close(shm_fd);
  shm_unlink(SHM_NAME);
  exit(EXIT_SUCCESS);
}
